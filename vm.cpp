#include <cassert>
#include <tuple>
#include <algorithm>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include "file_helpers.hpp"
#include "op.hpp"
#include "vm.hpp"
#include "warrior.hpp"
#include "read_helpers.hpp"

#define PROGRAM_OFFSET (PROG_NAME_LENGTH + 1) /* \0 (magic added before) */

using boost::adaptors::filtered;
using boost::range::for_each;

auto
read_warrior_name_prog(char const *path) {
  char *prog = file_helpers::read_file(path);
  int magic_number = read_helpers::read<int>(prog);
  if (magic_number != COREWAR_EXEC_MAGIC) {
    printf("%s is not a valid coretna champion (invalid magic number %d)\n", path, magic_number);
    throw VMInterruptException();
  }
  *prog += sizeof(int);

  return std::make_tuple(prog, prog + PROGRAM_OFFSET);
}


/* NOTE: do NOT pass num_warriors to vector constructor,
 * as it'd allocate these elements
 * instead of setting the max size... (duh)
 */
VM::VM(ulong num_warriors, opcode_map opcodes) : _opcodes{std::move(opcodes)},
                                                 _warriors{std::vector<Warrior>()},
                                                 _num_warriors{num_warriors},
                                                 _memory{} {
  _warriors.reserve(num_warriors);
}

void
VM::addWarrior(char *filename) {
  auto size = static_cast<int>(file_helpers::get_file_size(filename)) - PROGRAM_OFFSET;
  assert(size > 0);

  char *name;
  char const *prog;
  std::tie(name, prog) = read_warrior_name_prog(filename);

  uint id = _last_id++;
  _warriors.emplace_back(this, id, name, size, prog);
  uint offset = _last_id * (MEM_SIZE / _num_warriors);
  offset++; // TODO memcpy prog to the memory (just avoid unused var warning)
}

void
VM::run() {
  checkDone();

  for (;;) {
    for (auto &warrior: _warriors) {
      if (warrior.isWaiting()) {
        warrior.doWait();
      } else {
        warrior.play();
      }
    }
    runLifeCycle();

    if (checkDone())
      return;
  }
}

std::vector<Warrior> &
VM::getWarriors() {
  return _warriors;
}

auto
VM::getAliveWarriors() {
  return _warriors | filtered(std::mem_fn(&Warrior::isAlive));
}

unsigned long
VM::countAlive() const {
  return boost::size(_warriors | filtered(std::mem_fn(&Warrior::isAlive)));
}

uint
VM::getMaxCycles() const {
  return CYCLE_TO_DIE + CYCLE_DELTA * _delta;
}

bool
VM::checkDone() {
  switch (countAlive()) {
    case 0:
      printf("Aww, everyone died!\n");
      return true;

    case 1:
      printf("%s wins!\n", getAliveWarriors().front().getName().c_str());
      return true;
  }
  return false;
}

void
VM::runLifeCycle() {
  if (_cycle++ > getMaxCycles()) {
    _cycle = 0;
    _delta++;

    for_each(_warriors, [](auto &w) { w.tryToSurvive(); });
  }
}

op_t *
// TODO should this really be in VM? (reasoning: VM has the opcode map)
// TODO should this call the (NYI) "Warrior::useOp" method?
// XXX Warrior uses VM->getOpcodes()->find, doesn't make sense
VM::fetchOp(Warrior& warrior) {
//  uint pc = warrior->getPc();
//  readMemory<int>(pc);
//    T val = _parent_vm->readMemory<T>(_pc);
//    pc += sizeof(T);
//    pc %= MEM_SIZE;
//    return val;

  return nullptr; // TODO
}
