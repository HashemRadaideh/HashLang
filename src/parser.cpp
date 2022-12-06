#include "parser.hpp"

#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "node.hpp"
#include "token.hpp"
#include "types.hpp"

namespace HashLang {
Parser::Parser(std::string& line) {
  this->tokens = std::vector<struct Token>();

  class Lexer lexer = Lexer(line);

  struct Token token;
  do {
    token = lexer.getToken();
    if (token.type != Types::skip && token.type != Types::eof)
      this->tokens.emplace_back(token);
    lexer.next();
  } while (token.type != Types::eof);

  this->position = 0;
  this->current = this->tokens[this->position++];
  this->root = parse();
}

struct Node* Parser::getExpression() { return this->root; }

std::vector<struct Token> Parser::getTokens() { return this->tokens; }

void Parser::next() { this->current = this->tokens[this->position++]; }

struct Node* Parser::parse() { return parseTerm(); }

struct Node* Parser::parseTerm() {
  struct Node* left = parseFactor();

  while (current.type == Types::plus || current.type == Types::minus) {
    struct Token op = this->current;
    next();
    struct Node* right = parseFactor();

    struct Node* bin = new Node();
    bin->data = op;
    bin->left = left;
    bin->right = right;
    left = bin;
  }

  return left;
}

struct Node* Parser::parseFactor() {
  struct Node* left = parseCurrent();

  while (current.type == Types::slash || current.type == Types::asterisk) {
    struct Token op = this->current;
    next();
    struct Node* right = parseCurrent();

    struct Node* bin = new Node();
    bin->data = op;
    bin->left = left;
    bin->right = right;
    left = bin;
  }

  return left;
}

struct Node* Parser::parseCurrent() {
  if (this->current.type != Types::number) {
    return new Node();
  }

  auto node = new Node();
  node->data = this->current;
  next();

  return node;
}
}  // namespace HashLang
