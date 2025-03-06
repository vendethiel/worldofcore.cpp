#pragma once

#include <tuple>
#include "warrior.hpp"
#include "vm.hpp"
#include "read_helpers.hpp"

namespace instruction {
  namespace detail {
    template<typename... Ts>
    [[nodiscard]]
    std::tuple<> parse() {
      static_assert(sizeof...(Ts) <= 3);
      return {};
    }
  }

  int live(VM&, Warrior& warrior) {
    // TODO do we need to read flags?
    //[[maybe_unused]] auto _ = detail::parse<>();
    warrior.live();
    return 0;
  }
}
