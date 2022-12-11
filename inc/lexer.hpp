#pragma once

#include <string>

#include "token.hpp"

namespace Hash {
class Lexer {
 public:
  Lexer(std::string&);
  ~Lexer() = default;
  class Token getToken();
  void next();

 protected:
  class Token matcher(class Token);
  char peek(int);
  bool isNumber(char);
  bool isAlpha(char);

 private:
  std::string text;
  char current;
  int position;
};
}  // namespace Hash
