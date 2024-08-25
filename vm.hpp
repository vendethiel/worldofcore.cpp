#pragma once
#include <array>
#include <vector>
#include <unordered_map>
class Warrior;
#include "op.hpp"
#include "instruction.hpp"
#include "utility.hpp"
#include "read_helpers.hpp"

class VM {
public:
  VM(ulong num_warriors);

  void addWarrior(char* filename);

  void run();

  std::vector<Warrior>& getWarriors();
  auto getAliveWarriors();

  [[nodiscard]] unsigned long countAlive() const;
  [[nodiscard]] uint getMaxCycles() const;

  template<typename T>
  T
  readMemory(uint offset) {
    return read_helpers::read<T>(_memory.begin() + offset);
  }

private:
  bool checkDone();
  void runLifeCycle();

  std::vector<Warrior> _warriors;
  ulong _num_warriors;
  uint _last_id = 0;

  std::array<char, MEM_SIZE> _memory;

  unsigned int _cycle = 0;
  unsigned int _delta = 0;
};

class VMInterruptException : std::exception {
};
