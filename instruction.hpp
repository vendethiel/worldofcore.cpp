#pragma once

#include <tuple>
#include "vm.hpp"
#include "warrior.hpp"


namespace Instruction {
  struct VM_INT {
    using type = int;
  };

  namespace _impl {
    template<typename T>
    struct ArgFor {
    };

    template<>
    struct ArgFor<VM_INT> {
      using type = int;
    };

    template<typename... T>
    using ArgsFor = std::tuple<typename ArgFor<T>::type...>;
  }

  template<typename... T>
  struct Base {
    virtual void process(_impl::ArgsFor<T...> const &) = 0;

    ~Base() = default;
  };

  struct Live : Base<VM_INT> {
    void process(std::tuple<int> const &) override {

    }
  };
}
/*
typedef struct {
  char op;
  void (*fn)(vm_t* vm, warrior_t* warrior);
} instr_t;*/
/*
extern instr_t instructions[];
instr_t* find_instr(char);
char get_arg_type(int, char);
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