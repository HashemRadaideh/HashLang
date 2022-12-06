#pragma once

namespace HashLang {
enum class Types {
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

  unkown,
  skip,
  eof,
};
}  // namespace HashLang
