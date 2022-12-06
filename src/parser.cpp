#include "parser.hpp"

#include <functional>
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
    if (token.type != TokenType::skip && token.type != TokenType::eof)
      this->tokens.emplace_back(token);
    lexer.next();
  } while (token.type != TokenType::eof);

  this->position = 0;
  this->current = this->tokens[this->position++];
  this->root = parse();
}

Parser::~Parser() {
  std::function<void(struct Node*, std::function<void(struct Node*)>)> iterate =
      [&](struct Node* node,
          std::function<void(struct Node*)> function = nullptr) -> void {
    if (node == nullptr) return;

    iterate(node->left, function);
    iterate(node->right, function);

    function(node);
  };

  iterate(this->root, [](struct Node* node) -> void { delete node; });
}

struct Node* Parser::getExpression() { return this->root; }

std::vector<struct Token> Parser::getTokens() { return this->tokens; }

void Parser::next() { this->current = this->tokens[this->position++]; }

struct Node* Parser::parse() { return parseTerm(); }

bool Parser::match(enum TokenType type) { return this->current.type == type; }

struct Node* Parser::parseTerm() {
  struct Node* left = parseFactor();

  while (current.type == TokenType::plus || current.type == TokenType::minus) {
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

  while (current.type == TokenType::slash ||
         current.type == TokenType::asterisk) {
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
  if (match(TokenType::number)) {
    struct Node* node = new Node();
    node->data = this->current;
    next();
    return node;
  }

  return new Node();
}
}  // namespace HashLang
