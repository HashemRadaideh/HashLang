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
    token = lexer.nextToken();
    if (token.type != TokenType::skip && token.type != TokenType::eof)
      this->tokens.emplace_back(token);
    lexer.nextCharacter();
  } while (token.type != TokenType::eof);

  this->current = this->tokens[this->position++];
  parse();
}

struct Node Parser::getNode() { return this->baseNode; }

std::vector<struct Token> Parser::getTokens() { return this->tokens; }

struct Token Parser::next() { return this->tokens[++this->position]; }

struct Token Parser::match(enum TokenType type) {
  if (this->current.type == type) return next();
  return Token(type, nullptr, this->position);
}

Token Parser::peek(int offset) {
  int index = offset + this->position;
  if (index >= this->tokens.size()) return this->tokens[this->position - 1];
  return this->tokens[index];
}

struct Node* Parser::parseTerm() {
  Node* node = new Node();
  node->data = match(TokenType::number);
  return node;
}

struct Node Parser::parse() {
  struct Node bin = Node();

  bin.left = parseTerm();
  while (current.type == TokenType::plus || current.type == TokenType::minus) {
    bin.data = next();
    bin.right = parseTerm();
  }

  return bin;
}
}  // namespace HashLang
