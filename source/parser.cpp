#include "parser.hpp"

#include <functional>
#include <iostream>

#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "types.hpp"

namespace Hash {
Parser::Parser(std::string &line, bool printTokens = false) : lexer(line) {
  this->printTokens = printTokens;
  this->current = next();
  this->root = parse();
}

Parser::~Parser() { delete this->root; }

class Expression *Parser::getExpression() { return this->root; }

class Token Parser::next() {
  class Token token = lexer.getToken();
  lexer.next();

  if (printTokens) {
    if (token.getType() != Types::skip && token.getType() != Types::eof) {
      std::cout << token << std::endl;
    }
  }

  if (token.getType() == Types::skip) token = next();
  this->current = token;

  return token;
}

class Expression *Parser::parse() { return parseTerm(); }

class Expression *Parser::parseTerm() {
  class Expression *left = parseFactor();

  while (current.getType() == Types::plus ||
         current.getType() == Types::minus) {
    class Token op = this->current;
    next();
    class Expression *right = parseFactor();

    left = new Binary(left, op, right);
  }

  return left;
}

class Expression *Parser::parseFactor() {
  class Expression *left = parseCurrent();

  if (this->current.getType() == Types::open_parenthesis) {
    class Parenthesesed *node = new Parenthesesed();

    node->setOpen(this->current);
    next();

    node->setExpression(parseTerm());

    while (this->current.getType() == Types::skip) next();

    node->setClose(this->current);
    next();

    node->setToken(left->getToken());

    return node;
  }

  while (current.getType() == Types::power ||
         current.getType() == Types::slash ||
         current.getType() == Types::asterisk) {
    class Token op = this->current;
    next();
    class Expression *right = parseCurrent();

    left = new Binary(left, op, right);
  }

  return left;
}

class Expression *Parser::parseCurrent() {
  if (this->current.getType() == Types::plus ||
      this->current.getType() == Types::minus ||
      this->current.getType() == Types::bang) {
    class Unary *node = new Unary();

    node->setToken(this->current);
    next();

    node->setExpression(parseFactor());

    return node;
  }

  if (this->current.getType() == Types::number) {
    class Number *node = new Number(this->current);
    next();
    return node;
  }

  if (this->current.getType() == Types::string) {
    class String *node = new String(this->current);
    next();
    return node;
  }

  if (this->current.getType() == Types::boolean) {
    class Boolean *node = new Boolean(this->current);
    next();
    return node;
  }

  if (this->current.getType() == Types::open_parenthesis) {
    class Parenthesesed *node = new Parenthesesed();

    node->setOpen(this->current);
    next();

    node->setExpression(parseTerm());

    while (this->current.getType() == Types::skip) next();

    node->setClose(this->current);
    next();

    return node;
  }

  if (this->current.getType() == Types::eof) {
    return new Expression(Types::eof, this->current);
  }

  return new Expression();
}
}  // namespace Hash
