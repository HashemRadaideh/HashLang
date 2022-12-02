#pragma once

#include "token.hpp"
#include <string>
#include <vector>

namespace HashLang {
class Lexer {
public:
  Lexer(std::string);
  ~Lexer() = default;
  void printTokens();

protected:
  void nextToken();
  void nextCharacter();
  bool isNumber(char);

private:
  std::vector<Token> tokens;
  std::string text;
  char current;
  int posistion;
};
} // namespace HashLang
