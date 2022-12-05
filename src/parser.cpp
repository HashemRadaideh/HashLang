#include "parser.hpp"

#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "node.hpp"
#include "token.hpp"

namespace HashLang {
Parser::Parser(std::string line) {
  this->tokens = std::vector<struct Token>();

  class Lexer lexer = Lexer(line);

  struct Token token;
  do {
    token = lexer.getToken();
    if (token.type != TokenType::skip && token.type != TokenType::eof)
      this->tokens.emplace_back(token);
    lexer.next();
  } while (token.type != TokenType::eof);

  this->position = 0;
  this->current = this->tokens[this->position++];
  this->baseNode = parse();
}

struct Node Parser::getNode() { return this->baseNode; }

std::vector<struct Token> Parser::getTokens() { return this->tokens; }

void Parser::next() { this->current = this->tokens[this->position++]; }

struct Node Parser::parse() {
  struct Node root = Node();

  root.left = parseTerm();
  while (current.type == TokenType::plus || current.type == TokenType::minus) {
    root.data = this->current;
    next();
    root.right = parseTerm();

    if (current.type == TokenType::plus || current.type == TokenType::minus) {
      struct Node* bin = new Node();
      bin->data = root.data;
      bin->left = root.left;
      bin->right = root.right;
      root.left = bin;
    }
  }

  return root;
}

struct Node* Parser::parseTerm() {
  if (this->current.type != TokenType::number) {
    return new Node();
  }

  auto node = new Node();
  node->data = this->current;
  next();

  return node;
}

}  // namespace HashLang
