#pragma once
#include <array>
#include <vector>
#include <unordered_map>
class Warrior;
#include "op.hpp"
#include "read_helpers.hpp"

class VM {
public:
  using OpcodeMap = std::unordered_map<long, void(*)(VM&, Warrior&)>;
  VM(long num_warriors, OpcodeMap&& map);

  void addWarrior(char* filename);

  void run();

  std::vector<Warrior> const& getWarriors() const &;
  auto getAliveWarriors() const &;

  [[nodiscard]] unsigned long countAlive() const;
  [[nodiscard]] int getMaxCycles() const;

  template<typename T>
  T
  readMemory(int offset) {
    return read_helpers::read<T>(_memory.begin() + offset);
  }

private:
  bool checkDone() const;
  void runLifeCycle();

  OpcodeMap _opcodes;
  std::vector<Warrior> _warriors;
  long _num_warriors;
  int _last_id = 0;

  std::array<char, MEM_SIZE> _memory;

  int _cycle = 0;
  int _delta = 0;
};

class VMInterruptException : std::exception {
};
