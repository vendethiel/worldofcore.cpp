#pragma once
#include <array>
#include <vector>
#include <unordered_map>
class VM;
class Warrior;
#include "op.hpp"
#include "instruction.hpp"
#include "utility.hpp"
#include "read_helpers.hpp"

typedef void(*vm_op)(VM&, Warrior&);
typedef std::unordered_map<char, vm_op> opcode_map;

class VM {
public:
  VM(ulong num_warriors, opcode_map opcodes);

  void addWarrior(char* filename);

  void run();
  op_t* fetchOp(Warrior* warrior);

  std::vector<Warrior>& getWarriors();
  auto getAliveWarriors();

  [[nodiscard]] unsigned long countAlive() const;
  [[nodiscard]] uint getMaxCycles() const;
  [[nodiscard]] opcode_map const& getOpcodes() const;

  template<typename T>
  T
  readMemory(uint offset) {
    return read_helpers::read<T>(_memory.begin() + offset);
  }

private:
  bool checkDone();
  void runLifeCycle();

  opcode_map _opcodes;
  std::vector<Warrior> _warriors;
  ulong _num_warriors;
  uint _last_id = 0;

  std::array<char, MEM_SIZE> _memory;

  unsigned int _cycle = 0;
  unsigned int _delta = 0;
};

class VMInterruptException : std::exception {
};
