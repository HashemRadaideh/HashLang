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
  struct Node bin = Node();

  bin.left = new Node();
  bin.left->data = this->current;

  next();

  bin.data = this->current;

  next();

  bin.right = new Node();
  bin.right->data = this->current;

  return bin;
}
}  // namespace HashLang
