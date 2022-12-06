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

struct Node* Parser::parse() {
  struct Node* root = new Node();

  root->left = parseTerm();
  while (current.type == Types::forward_slash ||
         current.type == Types::asterisk || current.type == Types::plus ||
         current.type == Types::minus) {
    root->data = this->current;
    next();
    root->right = parseTerm();

    if (current.type == Types::forward_slash ||
        current.type == Types::asterisk || current.type == Types::plus ||
        current.type == Types::minus) {
      struct Node* bin = new Node();
      bin->data = root->data;
      bin->left = root->left;
      bin->right = root->right;
      root->left = bin;
    }
  }

  return root;
}

struct Node* Parser::parseTerm() {
  if (this->current.type != Types::number) {
    return new Node();
  }

  auto node = new Node();
  node->data = this->current;
  next();

  return node;
}
}  // namespace HashLang
