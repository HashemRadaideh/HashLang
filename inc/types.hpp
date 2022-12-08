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
  power,

  back_slash,

  open_parenthesis,
  close_parenthesis,

  parenthesised,

  unary,
  binary,
  ternary,

  statement,

  unkown,
  skip,
  eof,
};
}  // namespace HashLang
