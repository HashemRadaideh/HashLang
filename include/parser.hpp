#pragma once

#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"

namespace Hash {
class Parser {
 public:
  Parser(std::string &, bool);
  ~Parser();
  class Expression *getExpression();
  class Token next();
  class Expression *parse();
  class Expression *parseTerm();
  class Expression *parseFactor();
  class Expression *parseCurrent();

 private:
  bool printTokens;
  class Lexer lexer;
  class Expression *root;
  class Token current;
};
}  // namespace Hash
