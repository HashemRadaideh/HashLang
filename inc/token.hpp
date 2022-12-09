#pragma once

#include <string>

#include "types.hpp"

namespace Hash {
struct Token {
  Token(enum Types type = Types::unkown, std::string value = "", int start = 0,
        int end = 0) {
    this->type = type;
    this->value = value;
    this->start = start;
    this->end = (start > end) ? start : end;
  }

  ~Token() = default;

  enum Types type;
  std::string value;
  int start;
  int end;
};
}  // namespace HashLang
