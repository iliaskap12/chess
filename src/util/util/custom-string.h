#ifndef CHESS_CUSTOM_STRING_H
#define CHESS_CUSTOM_STRING_H

#include <string>
#include <vector>
#include <cstddef>

namespace custom_string {
  std::vector<std::string> split(const std::string &string, const std::string &delimiter);
}

// credits for constexpr hash function
// https://learnmoderncpp.com/2020/06/01/strings-as-switch-case-labels/

constexpr auto stringHash(const char *string) {
  unsigned long long hash { 0 };
  unsigned long long counter { 0 };

  for (auto pointer { string }; *pointer; ++pointer, ++counter) {
    hash += *pointer << counter;
  }

  return hash;
}

constexpr auto operator"" _hash(const char *string, std::size_t) {
  return stringHash(string);
}

#endif//CHESS_CUSTOM_STRING_H
