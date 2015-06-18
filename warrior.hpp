#pragma once
#include <string>
#include <assert.h>
#include "op.hpp"
class Warrior;

#include "vm.hpp"
#include "utility.hpp"

class Warrior : NonCopyable {
public:
  Warrior(VM* vm, uint id, std::string name, off_t prog_size, char const* prog)
      : _parent_vm{vm},
        _id{id},
        _name{std::move(name)},
        _prog_size{prog_size},
        _prog{prog}
  {
    _regs[0] = id;
  }

  std::string getName() const { return _name; }
  int getId() const { return _id; }
  bool isAlive() const { return _alive; }
  bool isWaiting() const;
  void doWait();

  void play();
  void didCallLive();
  void tryToSurvive();

  template<typename T>
  T
  readMemory() {
    T val = _parent_vm->readMemory<T>(_pc);
    _pc += sizeof(T);
    return val;
  }

private:
  void fetchNewOp();

  VM* _parent_vm;

  uint _id;
  std::string _name;

  long _prog_size;
  char const* _prog;

  int _next_instr = -1;
  uint _pc = 0;               /* that's really just a pointer */
  uint _waiting = 0; /* number of times before executing PC */

  bool _alive = true;
  bool _called_live = false;

  //short _carry = 0;
  int _regs[REG_NUMBER];

public:
  Warrior(Warrior&& that)
      : _parent_vm{that._parent_vm}, _id{that._id}, _name{std::move(that._name)},
        _prog_size{that._prog_size}, _prog{that._prog}
  {
    _regs[0] = that._id;
  };
};
