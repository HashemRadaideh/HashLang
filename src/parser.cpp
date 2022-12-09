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
  this->root = parse();
}

Parser::~Parser() { delete this->root; }

class Expression* Parser::getExpression() { return this->root; }

struct Token Parser::next() {
  struct Token token = lexer.getToken();
  lexer.next();

  if (printTokens) {
    if (token.type != Types::skip && token.type != Types::eof) {
      std::cout << "Token: " << type(token.type) << std::endl
                << "Value: " << token.content << std::endl
                << "At: " << token.start << " - " << token.end << std::endl;
    }
  }

  if (token.type == Types::skip) token = next();
  this->current = token;

  return token;
}

class Expression* Parser::parse() { return parseTerm(); }

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

  if (this->current.type == Types::open_parenthesis) {
    class Parenthesesed* node = new Parenthesesed();

    node->setOpen(this->current);
    next();

    node->setExpression(parseTerm());

    while (this->current.type == Types::skip) next();

    node->setClose(this->current);
    next();

    node->getToken(left->getValue());

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
  if (this->current.type == Types::plus || this->current.type == Types::minus ||
      this->current.type == Types::bang) {
    class Unary* node = new Unary();

    node->getToken(this->current);
    next();

    node->setExpression(parseFactor());

    return node;
  }

  if (this->current.type == Types::number) {
    class Number* node = new Number(this->current);
    next();
    return node;
  }

  if (this->current.type == Types::boolean) {
    class Boolean* node = new Boolean(this->current);
    next();
    return node;
  }

  if (this->current.type == Types::open_parenthesis) {
    class Parenthesesed* node = new Parenthesesed();

    node->setOpen(this->current);
    next();

    node->setExpression(parseTerm());

    while (this->current.type == Types::skip) next();

    node->setClose(this->current);
    next();

    return node;
  }

  if (this->current.type == Types::eof) {
    return new Expression(Types::eof, this->current);
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
