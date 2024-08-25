#pragma once

#include <tuple>
#include "warrior.hpp"
#include "read_helpers.hpp"

namespace Instruction {
  struct VM_INT {
  };

  namespace _impl {
    template<typename T>
    struct ArgFor {
      using type = int;
    };

    template<>
    struct ArgFor<VM_INT> {
      int parse(char* memory, uint& pc, int flag, int& nth) {
        nth++;

        pc += 2;
      }
    };

    template<typename... T>
    using ArgsFor = std::tuple<typename ArgFor<T>::type...> const &;
  }

  template<typename... T>
  struct Base {
    bool runIn(char *memory, Warrior &warrior);

    ~Base() = default;

  protected:
    virtual void process(_impl::ArgsFor<T...>, Warrior &) const = 0;
  };

  template<typename... T>
  bool Base<T...>::runIn(char *memory, Warrior &warrior) {
    uint pc = warrior.getPc();
    int flag = read_helpers::read<int>(memory + pc);
    pc += sizeof(int);
    int nth = 0;
    process(std::tuple{
      _impl::ArgFor<T>::parse(memory, pc, flag, nth)...
    }, memory, warrior);
  }

  struct Live : Base<> {
  protected:
    void process(std::tuple<> const &, Warrior &warrior) const override {
      warrior.live();
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