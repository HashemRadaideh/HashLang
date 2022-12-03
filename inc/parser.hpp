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

 private:
  std::vector<struct Token> tokens;
  struct Node baseNode;
};
}  // namespace HashLang