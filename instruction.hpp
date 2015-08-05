#pragma once
#include "vm.hpp"
#include "warrior.hpp"

class Instr {
public:
  virtual void run(VM& vm, Warrior& warrior);

protected:
  virtual ~Instruction() = 0;
};

// TODO move all this into separate files
namespace Instruction {

template<bool has_code, uint arg_num>
class Impl : Instr
public:
  void run(VM& vm, Warrior& warrior) override;

protected:
  typedef Instr super;

  Instr() {}

  const bool _has_code = has_code;
  const uint _arg_num = arg_num;
};


class Store : Impl<true, 2> {
public:
  // TODO: this method will most definitely call `super`
  // and receive a std::array<Argument, arg_num>
  void run(VM& vm, Warrior& warrior) override;
}

} // end namspace Instruction
