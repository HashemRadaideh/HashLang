#include "token.hpp"

namespace Hash {
Token::Token(enum Types type, std::string value, int start, int end) {
  this->type = type;
  this->content = value;
  this->start = start;
  this->end = (start > end) ? start : end;
}

Token::Token(enum Types type) {
  this->type = type;
  this->content = "";
  this->start = 0;
  this->end = 0;
}

Token::Token() {
  this->type = Types::unkown;
  this->content = "";
  this->start = 0;
  this->end = 0;
}

Token::~Token() {}

std::ostream &operator<<(std::ostream &os, const class Token &token) {
  return os << "Token: " << Token::getTypeof(token.type) << std::endl
            << "Value: " << token.content << std::endl
            << "At: " << token.start << " - " << token.end;
}

Types Token::getType() { return this->type; }

void Token::setType(enum Types type) { this->type = type; }

std::string Token::getContent() { return this->content; }

void Token::setContent(std::string value) { this->content = value; }

int Token::getStart() { return this->start; }

void Token::setStart(int position) { this->start = position; }

int Token::getEnd() { return this->end; }

void Token::setEnd(int position) { this->end = position; }

std::string Token::getTypeof(enum Types currentType) {
  if (currentType == Types::number)
    return "number literal";
  else if (currentType == Types::string)
    return "string literal";
  else if (currentType == Types::boolean)
    return "boolean literal";
  else if (currentType == Types::plus)
    return "plus operator";
  else if (currentType == Types::minus)
    return "minus operator";
  else if (currentType == Types::asterisk)
    return "asterisk operator";
  else if (currentType == Types::bang)
    return "bang operator";
  else if (currentType == Types::binary)
    return "binary expression";
  else if (currentType == Types::unary)
    return "unary expression";
  else if (currentType == Types::open_parenthesis)
    return "open parenthesis";
  else if (currentType == Types::close_parenthesis)
    return "close parenthesis";
  else if (currentType == Types::parenthesised)
    return "parenthesised expression";
  else if (currentType == Types::eof)
    return "EOF";
  return "Unkown token type";
}
}  // namespace Hash
