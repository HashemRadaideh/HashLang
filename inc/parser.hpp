#pragma once

#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "node.hpp"
#include "token.hpp"

namespace HashLang {
class Parser {
 public:
  Parser(std::string&);
  Parser() = default;
  ~Parser();
  class Expression* getExpression();
  struct Token next();
  bool match(enum Types);
  class Expression* parse();
  class Expression* parseTerm();
  class Expression* parseFactor();
  class Expression* parseCurrent();

 private:
  class Lexer lexer;
  class Expression* root;
  struct Token current;
};
}  // namespace HashLang
