#include "warrior.hpp"

void Warrior::tryToSurvive() {
  if (_called_live) {
    _called_live = false;
  } else {
    _alive = false; // awww RIP
  }
}

void Warrior::play() {
  if (_next_instr != -1) {
    // get an iterator
    auto op_it = _parent_vm->getOpcodes().find(readMemory<char>());
    if (op_it != _parent_vm->getOpcodes().end()) {
      auto op = std::get<vm_op>(*op_it); // deref iterator
      op(*_parent_vm, *this);
    }
  }
  _pc %= MEM_SIZE;
  if (_next_instr == -1) {
    // was not set by another instruction
    fetchNewOp();
  }
}

void Warrior::fetchNewOp() {
  op_t* op = nullptr; //FIXME find_op(_parent_vm->readMemory<char>(_pc));
  if (op) {
    _next_instr = _pc;
    _waiting = static_cast<uint>(op->nbr_cycles); // nbr_cycles is int? wtf?
  } else {
    _pc++; /* skip that one, cya later ... */
  }
  _pc %= MEM_SIZE;
}
