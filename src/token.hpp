#pragma once

#include <string>

namespace HashLang {
enum class TokenType {
  unkown,
  skip,

  keyword,

  number,
  string,

  equal,
  plus,
  minus,
  asterisk,
  forward_slash,
  backward_slash,
  left_parenthesis,
  right_parenthesis,
};

struct Token {
  TokenType type;
  std::string value;
  int start;
  int end;

  Token(TokenType type = TokenType::unkown, std::string value = "",
        int start = 0, int end = 0) {
    this->type = type;
    this->value = value;
    this->start = start;
    this->end = (start > end) ? start : end;
  }
};
}  // namespace HashLang
