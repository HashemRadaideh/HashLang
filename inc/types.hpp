#pragma once

namespace HashLang {
enum class Types {
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

  unary,
  binary,
  ternary,

  statement,

  unkown,
  skip,
  eof,
};
}  // namespace HashLang
