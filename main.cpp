#include "warrior.hpp"
#include "vm.hpp"
#include "instruction.hpp"

int main(int argc, char** argv)
{
  VM::OpcodeMap opcodes = {};
  VM vm(argc - 1, std::move(opcodes));

  for (int i = 1; i < argc; ++i) {
    vm.addWarrior(argv[i]);
  }
  try {
    vm.run();
  } catch (VMInterruptException& _ex) {
    // well, here we are, burning...
  }
  return 0;
}
