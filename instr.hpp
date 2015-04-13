#ifndef INSTR_H_
#define INSTR_H_

/*
typedef struct {
  char op;
  void (*fn)(vm_t* vm, warrior_t* warrior);
} instr_t;*/
/*
extern instr_t instructions[];
instr_t* find_instr(char);
 */
char get_arg_type(int, char);
/*
void instr_live(vm_t* vm, warrior_t* warrior);
void instr_ld(vm_t* vm, warrior_t* warrior);
void instr_st(vm_t* vm, warrior_t* warrior);
void instr_add(vm_t* vm, warrior_t* warrior);
void instr_sub(vm_t* vm, warrior_t* warrior);
void instr_and(vm_t* vm, warrior_t* warrior);
void instr_or(vm_t* vm, warrior_t* warrior);
void instr_xor(vm_t* vm, warrior_t* warrior);
void instr_zjmp(vm_t* vm, warrior_t* warrior);
void instr_ldi(vm_t* vm, warrior_t* warrior);
void instr_sti(vm_t* vm, warrior_t* warrior);
void instr_fork(vm_t* vm, warrior_t* warrior);
void instr_lld(vm_t* vm, warrior_t* warrior);
void instr_lldi(vm_t* vm, warrior_t* warrior);
void instr_lfork(vm_t* vm, warrior_t* warrior);
void instr_aff(vm_t* vm, warrior_t* warrior);
*/
#endif
