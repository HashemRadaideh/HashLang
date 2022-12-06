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
  ~Parser();
  struct Node* getExpression();
  std::vector<struct Token> getTokens();
  void next();
  bool match(enum TokenType);
  struct Node* parse();
  struct Node* parseTerm();
  struct Node* parseFactor();
  struct Node* parseCurrent();

 private:
  struct Node* root;
  std::vector<struct Token> tokens;
  struct Token current;
  int position;
};
}  // namespace HashLang
