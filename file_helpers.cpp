#include <string>
#include <fstream>
#include "file_helpers.hpp"

std::ifstream::pos_type
file_helpers::get_file_size(char const *filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  return in.tellg();
}

char*
file_helpers::read_file(char const *filename) {
  std::ifstream t(filename);
  std::string str{
      std::istreambuf_iterator<char>(t),
      std::istreambuf_iterator<char>()
  };
  return strdup(str.c_str());
};
