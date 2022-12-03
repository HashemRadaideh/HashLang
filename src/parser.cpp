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
}

struct Node Parser::getNode() { return this->baseNode; }

std::vector<struct Token> Parser::getTokens() { return this->tokens; }
}  // namespace HashLang
