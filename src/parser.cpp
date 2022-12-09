#include "parser.hpp"

#include <functional>
#include <iostream>

#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "types.hpp"

namespace Hash {
Parser::Parser(std::string& line, bool printTokens = false) : lexer(line) {
  this->printTokens = printTokens;
  this->current = next();
  if (this->current.type != Types::eof) this->root = parse();
}

Parser::~Parser() { delete this->root; }

class Expression* Parser::getExpression() { return this->root; }

struct Token Parser::next() {
  struct Token token = lexer.getToken();
  lexer.next();

  if (printTokens) {
    if (token.type != Types::skip && token.type != Types::eof) {
      std::cout << "Token: " << type(token.type) << std::endl
                << "Value: " << token.value << std::endl
                << "At: " << token.start << " - " << token.end << std::endl;
    }
  }

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

    left = new Binary(left, op, right);
  }

  return left;
}

class Expression* Parser::parseFactor() {
  class Expression* left = parseCurrent();

  if (match(Types::open_parenthesis)) {
    class Parenthesesed* node = new Parenthesesed();

    node->setOpen(this->current);
    next();

    node->setExpression(parseTerm());

    while (match(Types::skip)) next();

    node->setClose(this->current);
    next();

    node->setValue(left->getValue());

    return node;
  }

  while (current.type == Types::power || current.type == Types::slash ||
         current.type == Types::asterisk) {
    struct Token op = this->current;
    next();
    class Expression* right = parseCurrent();

    left = new Binary(left, op, right);
  }

  return left;
}

class Expression* Parser::parseCurrent() {
  if (match(Types::plus) || match(Types::minus) || match(Types::bang)) {
    class Unary* node = new Unary();

    node->setValue(this->current);
    next();

    node->setExpression(parseTerm());

    return node;
  }

  if (match(Types::number)) {
    class Number* node = new Number();
    node->setValue(this->current);
    next();
    return node;
  }

  if (match(Types::boolean)) {
    class Boolean* node = new Boolean();
    node->setValue(this->current);
    next();
    return node;
  }

  if (match(Types::open_parenthesis)) {
    class Parenthesesed* node = new Parenthesesed();

    node->setOpen(this->current);
    next();

    node->setExpression(parseTerm());

    while (match(Types::skip)) next();

    node->setClose(this->current);
    next();

    return node;
  }

  return new Expression();
}

std::string Parser::type(enum Types type) {
  if (type == Types::number)
    return "number literal";
  else if (type == Types::string)
    return "string literal";
  else if (type == Types::boolean)
    return "boolean literal";
  else if (type == Types::plus)
    return "plus operator";
  else if (type == Types::minus)
    return "minus operator";
  else if (type == Types::asterisk)
    return "asterisk operator";
  else if (type == Types::bang)
    return "bang operator";
  else if (type == Types::binary)
    return "binary expression";
  else if (type == Types::unary)
    return "unary expression";
  else if (type == Types::open_parenthesis)
    return "open parenthesis";
  else if (type == Types::close_parenthesis)
    return "close parenthesis";
  else if (type == Types::parenthesised)
    return "parenthesised expression";
  return "Unkown token type";
}
}  // namespace Hash
