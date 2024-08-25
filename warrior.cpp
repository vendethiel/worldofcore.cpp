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

uint Warrior::getPc() const {
  return _pc;
}

void Warrior::setPc(uint pc) {
  _pc = pc;
}

void Warrior::live() {
  _called_live = true;
}
