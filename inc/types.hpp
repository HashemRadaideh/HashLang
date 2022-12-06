#pragma once

namespace HashLang {
enum class TokenType {
  identifier,

  number,
  string,

  equal,
  plus,
  minus,
  asterisk,
  slash,
  back_slash,
  open_parenthesis,
  close_parenthesis,

  unkown,
  skip,
  eof,
};

enum class SyntaxType {
  unary,
  binary,
  ternary,
  statement,
};
}  // namespace HashLang
