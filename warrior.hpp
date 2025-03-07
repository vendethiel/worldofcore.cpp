#pragma once
#include <string>
#include <array>
#include <sys/types.h>

#include "op.hpp"

class Warrior {
public:
  Warrior(uint id, std::string name, off_t prog_size, char const* prog);
  Warrior(Warrior&& that) noexcept;

  Warrior(Warrior const&) = delete;
  Warrior& operator=(Warrior const&) = delete;

  [[nodiscard]] std::string&& getName() &&;
  [[nodiscard]] std::string const& getName() const &;
  [[nodiscard]] uint getId() const;
  [[nodiscard]] bool isAlive() const;
  [[nodiscard]] bool isWaiting() const;
  void doWait();

  int& reg(int idx) &;
  int const& reg(int idx) const &;

  void live();
  [[nodiscard]] int getPc() const;
  void setPc(uint);
  void tryToSurvive();

private:
  uint _id;
  std::string _name;

  long _prog_size;
  char const* _prog;

  int _next_instr = -1;
  int _pc = 0;               /* that's really just a pointer */
  uint _waiting = 0; /* number of times before executing PC */

  bool _alive = true;
  bool _called_live = false;

  std::array<int, REG_NUMBER> _regs;
};
