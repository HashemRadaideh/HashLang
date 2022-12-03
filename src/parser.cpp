#include "parser.hpp"

#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "node.hpp"
#include "token.hpp"

namespace HashLang {
Parser::Parser(std::string line) {
  this->lexer = Lexer(line);
  this->tokens = this->lexer.getTokens();
}

struct Node Parser::getNodes() { return this->baseNode; }

void Parser::printTree(struct Node node, std::string indent = "",
                       bool isLast = true) {
  // │
  // ├──
  // └──
  std::string branch = isLast ? "└──" : "├──";
  std::cout << indent << branch;

  if (baseNode.data.type == TokenType::number)
    std::cout << "number";
  else if (baseNode.data.type == TokenType::string)
    std::cout << "string";
  else if (baseNode.data.type == TokenType::plus)
    std::cout << "plus";
  else if (baseNode.data.type == TokenType::minus)
    std::cout << "minus";
  else if (baseNode.data.type == TokenType::asterisk)
    std::cout << "asterisk";
  else if (baseNode.data.type == TokenType::forward_slash)
    std::cout << "forward";
  else
    std::cerr << "Unkown";

  std::cout << std::endl;

  indent += isLast ? "   " : "│   ";

  bool isLastChild = true;

  printTree(node, indent, isLastChild);
}
}  // namespace HashLang
