#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

namespace HashLang {
class Lexer {
 public:
  Lexer() = default;
  Lexer(std::string);
  ~Lexer() = default;
  std::vector<struct Token> getTokens();
  void printTokens();

 protected:
  struct Token nextToken();
  void nextCharacter();
  bool isNumber(char);

 private:
  std::vector<struct Token> tokens;
  std::string text;
  char current;
  int posistion;
};
}  // namespace HashLang
