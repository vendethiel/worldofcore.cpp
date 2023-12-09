#pragma once
#include <fstream>

namespace file_helpers {
  std::ifstream::pos_type get_file_size(char const*);

  std::string read_file(char const*);
}
