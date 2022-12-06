#include "parser.hpp"

#include <functional>
#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "node.hpp"
#include "token.hpp"
#include "types.hpp"

namespace HashLang {
Parser::Parser(std::string& line) : lexer(line) {
  this->current = next();
  if (this->current.type != Types::eof) this->root = parse();
}

Parser::~Parser() { delete root; }

class Expression* Parser::getExpression() { return this->root; }

struct Token Parser::next() {
  struct Token token = lexer.getToken();
  lexer.next();

  if (token.type == Types::skip) token = next();

  return token;
}

class Expression* Parser::parse() { return parseTerm(); }

bool Parser::match(enum Types type) { return this->current.type == type; }

class Expression* Parser::parseTerm() {
  class Expression* left = parseFactor();

  while (current.type == Types::plus || current.type == Types::minus) {
    struct Token op = this->current;
    this->current = next();
    class Expression* right = parseFactor();

    class BinaryExpression* bin = new BinaryExpression();
    bin->left = left;
    bin->op = op;
    bin->right = right;
    left = bin;
  }

  return left;
}

class Expression* Parser::parseFactor() {
  class Expression* left = parseCurrent();

  while (current.type == Types::slash || current.type == Types::asterisk) {
    struct Token op = this->current;
    this->current = next();
    class Expression* right = parseCurrent();

    class BinaryExpression* bin = new BinaryExpression();
    bin->left = left;
    bin->op = op;
    bin->right = right;
    left = bin;
  }

  return left;
}

class Expression* Parser::parseCurrent() {
  if (match(Types::number)) {
    class Number* node = new Number();
    node->number = this->current;
    this->current = next();
    return node;
  }

  return new Expression();
}
}  // namespace HashLang
