#include "warrior.hpp"

Warrior::Warrior(VM *vm, uint id, std::string name, off_t prog_size, char const *prog)
        : _parent_vm{vm},
          _id{id},
          _name{std::move(name)},
          _prog_size{prog_size},
          _prog{prog},
          _regs{static_cast<int>(id)} {
}

Warrior::Warrior(Warrior &&that) noexcept
        : _parent_vm{that._parent_vm},
          _id{that._id},
          _name{std::move(that._name)},
          _prog_size{that._prog_size},
          _prog{that._prog},
          _regs{static_cast<int>(that._id)} {
}

void
Warrior::doWait() {
  assert(_waiting > 0);
  _waiting--;
}

bool
Warrior::isWaiting() const {
  return _waiting > 0;
}

void
Warrior::didCallLive() {
  _called_live = true;
}

std::string
Warrior::getName() const {
  return _name;
}

uint
Warrior::getId() const {
  return _id;
}

bool
Warrior::isAlive() const {
  return _alive;
}

void
Warrior::tryToSurvive() {
  if (_called_live) {
    _called_live = false;
  } else {
    _alive = false; // awww RIP
  }
}

void
Warrior::play() {
  if (_next_instr != -1) {
    // get an iterator
    // TODO ->getOpcode(readMemory()), don't provide getOpcodes()
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
  op_t *op = _parent_vm->fetchOp(this);
  // find_op(_parent_vm->readMemory<char>(_pc));
  if (op) {
    _next_instr = static_cast<int>(_pc);
    _waiting = static_cast<uint>(op->nbr_cycles); // nbr_cycles is int? wtf?
  } else {
    _pc++; /* skip that one, cya later ... */
  }
  _pc %= MEM_SIZE;
}