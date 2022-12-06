#pragma once

#include <string>

#include "types.hpp"

namespace HashLang {
struct Token {
  enum TokenType type;
  std::string value;
  int start;
  int end;

  Token(enum TokenType type = TokenType::unkown, std::string value = "",
        int start = 0, int end = 0) {
    this->type = type;
    this->value = value;
    this->start = start;
    this->end = (start > end) ? start : end;
  }
  ~Token() = default;
};
}  // namespace HashLang
