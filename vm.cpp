#include <assert.h>
#include <tuple>
#include <algorithm>
#include <string>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include "file_helpers.hpp"
#include "op.hpp"
#include "warrior.hpp"
#include "read_helpers.hpp"

#define PROGRAM_OFFSET PROG_NAME_LENGTH + 1 /* \0 (magic added before) */

using boost::adaptors::filtered;
using boost::range::for_each;

auto
read_warrior_name_prog(char const* path) {
  char const* prog = file_helpers::read_file(path);
  int magic_number = read_helpers::read<int>(prog);
  if (magic_number != COREWAR_EXEC_MAGIC) {
    printf("%s is not a valid coretna champion (invalid magic number %d)\n", path, magic_number);
    throw VMInterruptException();
  }
  prog += sizeof(int);

  return std::make_tuple(std::string(prog), prog + PROGRAM_OFFSET);
}

void
VM::addWarrior(char *filename) {
  auto size = static_cast<int>(file_helpers::get_file_size(filename)) - PROGRAM_OFFSET;
  assert(size > 0);

  std::string name;
  char const* prog;
  std::tie(name, prog) = read_warrior_name_prog(filename);

	uint id = _last_id++;
  _warriors.emplace_back(this, id, name, size, prog);
	uint offset = _last_id * (MEM_SIZE / _num_warriors);
	offset++; // TODO memcpy prog to
}

void
VM::run() {
  checkDone();

  for (;;) {
    for (auto& warrior : _warriors) {
      if (warrior.isWaiting()) {
        warrior.doWait();
      } else {
        warrior.play();
      }
    }
    runLifeCycle();

    checkDone();
  }
}

std::vector<Warrior>&
VM::getWarriors() {
  return _warriors;
}

auto
VM::getAliveWarriors() {
  return _warriors | filtered(std::mem_fn(&Warrior::isAlive));
}

bool
VM::isDone() const {
  return countAlive() < 2;
}

long
VM::countAlive() const {
  return boost::size(_warriors
         | filtered([](auto const& w){ return w.isAlive(); }));
}

uint
VM::getMaxCycles() const {
  return CYCLE_TO_DIE + CYCLE_DELTA * _delta;
}

opcode_map const&
VM::getOpcodes() const {
  return _opcodes;
}

void
VM::checkDone() {
  switch (countAlive()) {
    case 0:
      printf("Aww, everyone died!\n");
      throw VMInterruptException();

    case 1:
      printf("%s wins!\n", getAliveWarriors().front().getName().c_str());
      throw VMInterruptException();
  }
}

void
VM::runLifeCycle() {
  if (_cycle++ > getMaxCycles()) {
    _cycle = 0;
    _delta++;

    for_each(_warriors, [](auto& w) { w.tryToSurvive(); });
  }
}

/*
void fetch_op(vm_t * vm, warrior_t * warrior) {
  op_t *op = find_op(vm->memory[warrior->pc]);
  if (op) {
    warrior->next_instr = warrior->pc;
    warrior->waiting = op->nbr_cycles;
  } / * else, just wait it out * /
  warrior->pc %= MEM_SIZE; / * so circular... * /
}


*/
