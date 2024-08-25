#pragma once
#include <string>
#include <cassert>
#include "utility.hpp"

class Warrior : NonCopyable {
public:
  Warrior(VM* vm, uint id, std::string name, off_t prog_size, char const* prog);
  Warrior(Warrior&& that) noexcept;

  [[nodiscard]] std::string getName() const;
  [[nodiscard]] uint getId() const;
  [[nodiscard]] bool isAlive() const;
  [[nodiscard]] bool isWaiting() const;
  void doWait();

  void live();
  uint getPc() const;
  void setPc(uint);
  void tryToSurvive();

private:
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
  [[maybe_unused]] int _regs[REG_NUMBER];
};
