#include <boost/range.hpp>
#include "instr_header.hpp"

void instr_live(VM &vm, Warrior &warrior) {
  int warrior_id = warrior.readMemory<int>();
  auto war = first_where(vm.getWarriors(),
                     [warrior_id](auto& w) { return w.getId() == warrior_id; });
  if (war) {
    printf("%s will live!\n", war->getName().c_str());
    war->didCallLive();
  } else {
    printf("Random live called, but no warrior with given ID...\n");
  }
}
/*
void instr_zjmp(vm_t* vm, warrior_t* warrior)
{
	/ * NO CODE OCTET * /
	int index vm_read_int(vm, warrior);
	if (!warrior->carry) {
		return; / * zjmp is conditional * /
	}
	this->pc += index * IDX_MOD;
}

void instr_aff(vm_t* vm, warrior_t* warrior)
{
  rip("tbd aff");
}*/
