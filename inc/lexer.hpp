#pragma once

#include <string>

#include "token.hpp"

namespace HashLang {
class Lexer {
 public:
  Lexer(std::string&);
  ~Lexer() = default;
  struct Token getToken();
  void next();

 protected:
  char peek(int);
  bool isNumber(char);
  bool isAlpha(char);

 private:
  std::string text;
  char current;
  int position;
};
}  // namespace HashLang
