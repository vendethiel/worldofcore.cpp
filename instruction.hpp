#pragma once

#include <tuple>
#include "warrior.hpp"
#include "vm.hpp"
#include "read_helpers.hpp"

namespace instruction {
  namespace detail {
    struct Register {
      static constexpr int flag = 0x1;
      static int accept(int given, int raw, Warrior const& warrior) {
        if (given == flag)
          return warrior.reg(raw);
        return -1;
      }
    };
    struct Value {
      static constexpr int flag = 0x2;
      static int accept(int given, int raw, Warrior const&) {
        if (given == flag)
          return raw;
        return -1;
      }
    };

    template<typename... Ts>
    struct Either;

    template<typename T, typename... Ts>
    struct Either<T, Ts...> {
      static int accept(int flag, int raw, Warrior const& warrior) {
        int ret = T::accept(flag, raw, warrior);
        return ret == -1 ? Either<Ts...>::accept(flag, raw, warrior) : ret;
      }
    };

    template<>
    struct Either<> {
      static int accept(int, int, Warrior const&) {
        return -1; // TODO signal error? skip warrior's turn?
      }
    };

    using Any = Either<Register, Value>;

//    template<typename T>
//    int callParse(int flags, int raw, Warrior const& warrior) {
//      return return T::parse(flags, raw
//    }

    template<auto T, typename R>
    using As = R;

    template<typename... Ts>
    requires (sizeof...(Ts) <= 3)
    [[nodiscard]]
    auto parse(VM& vm, Warrior& warrior) {
      int pc = warrior.getPc();
      int flagsValue = vm.readMemory<int>(pc);
      pc += 2;
      warrior.setPc(pc + (1 + sizeof...(Ts))); // increment it, but keep pc here for expansion
      std::array<int, 3> flags = { flagsValue & 0x11, flagsValue & 0x1100, flagsValue & 0x110000 };

      using Tst = std::tuple<Ts...>;
      return [&vm, &warrior, flags, pc]<std::size_t... I>(std::index_sequence<I...>) {
        return std::tuple<as<I, int>...>(
          std::tuple_element<I, Tst>::type::accept(flags[I], vm.readMemory<int>(pc + (I * 2)), warrior)...
        );
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
  }


  void live(VM&, Warrior& warrior) {
    // TODO do we need to read flags?
    //[[maybe_unused]] auto _ = detail::parse<>();
    warrior.live();
  }

  void ld(VM& vm, Warrior& warrior) {
    using namespace detail;
    const auto [reg, reg2] = detail::parse<detail::Register, detail::Register>(vm, warrior);
    warrior.reg(reg) = warrior.reg(reg2);
  }

  void st(VM& vm, Warrior& warrior) {
    const auto [reg, value] = detail::parse<detail::Register, detail::Any>(vm, warrior);
    warrior.reg(reg) = value;
  }
}
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
