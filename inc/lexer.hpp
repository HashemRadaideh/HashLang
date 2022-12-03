#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

namespace HashLang {
class Lexer {
 public:
  Lexer(std::string);
  ~Lexer() = default;
  struct Token nextToken();
  void nextCharacter();

 protected:
  bool isNumber(char);

 private:
  std::string text;
  char current;
  int position;
};
}  // namespace HashLang
