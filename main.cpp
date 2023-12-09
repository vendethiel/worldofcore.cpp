#include <memory>
#include <vector>
#include <unordered_map>
#include "warrior.hpp"
#include "vm.hpp"
#include "instructions/other.cpp"

int main(int argc, char** argv)
{
  VM vm(static_cast<ulong>(argc - 1), {
      {0x01, instr_live},
  });

  for (int i = 1; i < argc; ++i) {
    vm.addWarrior(argv[i]);
  }
  try {
    vm.run();
  } catch (VMInterruptException& ex) {
    // well, here we are, burning...
  }
  return 0;
}
