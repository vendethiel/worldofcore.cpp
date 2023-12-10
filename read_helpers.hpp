#pragma once

#include <cstddef>

namespace read_helpers {
  template<typename T>
  T read(char* bytes) {
    char tmp[sizeof(T)];

    for (size_t i = sizeof(tmp); i--; ++bytes)
      tmp[i] = *bytes;

    return *static_cast<T*>(static_cast<void*>(tmp));
  }
}