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
  struct Node getNodes();
  void printTree(struct Node, std::string, bool);

 private:
  Lexer lexer;
  struct Node baseNode;
  std::vector<struct Token> tokens;
};
}  // namespace HashLang