#include "parser.hpp"

#include <functional>

#include "ast.hpp"
#include "lexer.hpp"
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
  this->current = token;

  return token;
}

class Expression* Parser::parse() { return parseTerm(); }

bool Parser::match(enum Types type) { return this->current.type == type; }

class Expression* Parser::parseTerm() {
  class Expression* left = parseFactor();

  while (current.type == Types::plus || current.type == Types::minus) {
    struct Token op = this->current;
    next();
    class Expression* right = parseFactor();

    class Binary* bin = new Binary();
    bin->left = left;
    bin->token = op;
    bin->right = right;
    left = bin;
  }

  return left;
}

class Expression* Parser::parseFactor() {
  class Expression* left = parseCurrent();

  if (match(Types::open_parenthesis)) {
    class Parenthesesed* node = new Parenthesesed();

    node->open = this->current;
    next();

    auto parsed = parseTerm();
    node->expression = (Binary*)parsed;

    while (match(Types::skip)) next();

    node->close = this->current;
    next();

    node->token = left->token;

    return node;
  }

  while (current.type == Types::power || current.type == Types::slash ||
         current.type == Types::asterisk) {
    struct Token op = this->current;
    next();
    class Expression* right = parseCurrent();

    class Binary* bin = new Binary();
    bin->left = left;
    bin->token = op;
    bin->right = right;
    left = bin;
  }

  return left;
}

class Expression* Parser::parseCurrent() {
  if (match(Types::plus) || match(Types::minus) || match(Types::bang)) {
    class Unary* node = new Unary();

    node->token = this->current;
    next();

    class Expression* parsed = parseTerm();
    node->expression = parsed;

    return node;
  }

  if (match(Types::number)) {
    class Number* node = new Number();
    node->token = this->current;
    next();
    return node;
  }

  if (match(Types::boolean)) {
    class Boolean* node = new Boolean();
    node->token = this->current;
    next();
    return node;
  }

  if (match(Types::open_parenthesis)) {
    class Parenthesesed* node = new Parenthesesed();

    node->open = this->current;
    next();

    auto parsed = parseTerm();
    node->expression = parsed;

    while (match(Types::skip)) next();

    node->close = this->current;
    next();

    return node;
  }

  return new Expression();
}
}  // namespace HashLang
