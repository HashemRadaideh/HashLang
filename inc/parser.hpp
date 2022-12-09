#pragma once

#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"

namespace Hash {
class Parser {
 public:
  Parser(std::string&, bool);
  Parser() = default;
  ~Parser();
  class Expression* getExpression();
  struct Token next();
  bool match(enum Types);
  class Expression* parse();
  class Expression* parseTerm();
  class Expression* parseFactor();
  class Expression* parseCurrent();
  std::string type(enum Types);

 private:
  bool printTokens;
  class Lexer lexer;
  class Expression* root;
  struct Token current;
};
}  // namespace Hash
