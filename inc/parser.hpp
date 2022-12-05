#pragma once

#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "node.hpp"
#include "token.hpp"

namespace HashLang {
class Parser {
 public:
  Parser(std::string);
  ~Parser() = default;
  struct Node getNode();
  std::vector<struct Token> getTokens();
  void next();
  struct Node parse();
  struct Node* parseTerm();

 private:
  std::vector<struct Token> tokens;
  struct Token current;
  int position;
  struct Node baseNode;
};
}  // namespace HashLang