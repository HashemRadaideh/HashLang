#pragma once

namespace Hash {
enum class Types {
  identifier,
  keyword,

  number,
  boolean,
  string,

  equal,

  plus,
  minus,
  asterisk,
  slash,
  power,

  back_slash,

  bang,

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
