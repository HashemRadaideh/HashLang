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
  struct Node* getExpression();
  struct Token next();
  bool match(enum TokenType);
  struct Node* parse();
  struct Node* parseTerm();
  struct Node* parseFactor();
  struct Node* parseCurrent();

 private:
  class Lexer lexer;
  struct Node* root;
  struct Token current;
};
}  // namespace HashLang
