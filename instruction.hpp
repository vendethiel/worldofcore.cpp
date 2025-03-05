#pragma once

#include <tuple>
#include "warrior.hpp"
#include "vm.hpp"
#include "read_helpers.hpp"

/*
namespace __Instruction {
  struct VM_INT {
  };

  template<typename...>
  struct Allowed{};

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

  struct Base {
    virtual void operator()() = 0;
    virtual ~Base() = 0;
  };

  inline Base::~Base() = default;

  template<typename... T>
  struct Of : Base {
    bool runIn(char *memory, Warrior &warrior);

  protected:
    virtual void process(_impl::ArgsFor<T...>, Warrior &) const = 0;
  };

  template<typename... T>
  bool Of<T...>::runIn(char *memory, Warrior &warrior) {
    uint pc = warrior.getPc();
    int flag = read_helpers::read<int>(memory + pc);
    pc += sizeof(int);
    int nth = 0;
    process(std::tuple{
      _impl::ArgFor<T>::parse(memory, pc, flag, nth)...
    }, memory, warrior);
    return true;
  }

  struct Live : Of<> {
  protected:
    void process(std::tuple<> const &, Warrior &warrior) const override {
      warrior.live();
    }
  };
}
*/

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


/**
 * TODO, better plan:

void instr_live(VM const&, int flags) {
  const args = getArgs<><Allowed<Register, Direct>, Allowed<Indirect, Direct>>(vm, flags);
  ...
}
=> OpcodeMap can be `void(*)(...);`
*/

namespace instruction {
  namespace detail {
    template<typename... Ts>
    [[nodiscard]]
    std::tuple<> parse() {
      static_assert(sizeof...(Ts) <= 3);
      return {};
    }
  }

  void live(VM&, Warrior& warrior) {
    // TODO do we need to read flags?
    //[[maybe_unused]] auto _ = detail::parse<>();
    warrior.live();
  }
}
