#pragma once

#include <stddef.h>

namespace read_helpers {
  template<typename T>
  T read(char const* bytes) {
    char tmp[sizeof(T)];

    for (size_t i = sizeof(tmp); i--; ++bytes)
      tmp[i] = *bytes;

    return *static_cast<T*>(static_cast<void*>(tmp));
  }
}