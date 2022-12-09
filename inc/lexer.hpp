#pragma once

#include <string>

#include "token.hpp"

namespace Hash {
class Lexer {
 public:
  Lexer(std::string&);
  ~Lexer() = default;
  struct Token getToken();
  void next();

 protected:
  struct Token matcher(struct Token);
  char peek(int);
  bool isNumber(char);
  bool isAlpha(char);

 private:
  std::string text;
  char current;
  int position;
};
}  // namespace HashLang
