#pragma once

#include <string>
#include <vector>

#include "token.hpp"

namespace HashLang {
class Lexer {
 public:
  Lexer(std::string);
  ~Lexer() = default;
  void printTokens();

 protected:
  Token nextToken();
  void nextCharacter();
  void backCharacter();
  bool isNumber(char);

 private:
  std::vector<Token> tokens;
  std::string text;
  char current;
  int posistion;
};
}  // namespace HashLang
