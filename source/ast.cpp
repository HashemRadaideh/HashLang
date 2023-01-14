#include "ast.hpp"

#include "types.hpp"

namespace Hash {
Expression::Expression(enum Types type, class Token token) {
  this->type = type;
  this->token = token;
}

Expression::Expression() { this->type = Types::unkown; }

Expression::~Expression() {}

void Expression::setType(enum Types type) { this->type = type; }

enum Types Expression::getType() { return this->type; }

class Token Expression::getToken() { return this->token; }

void Expression::setToken(class Token token) { this->token = token; }

Number::Number(class Token number) {
  this->setType(Types::number);
  this->setToken(number);
}

Number::Number() { this->setType(Types::number); }

Number::~Number() {}

Boolean::Boolean(class Token boolean) {
  this->setType(Types::boolean);
  this->setToken(boolean);
}

Boolean::Boolean() { this->setType(Types::boolean); }

Boolean::~Boolean() {}

Unary::Unary(class Token op, class Expression *expression) {
  this->setType(Types::unary);
  this->setToken(op);
  this->expression = expression;
}

Unary::Unary() { this->setType(Types::unary); }

Unary::~Unary() { delete expression; }

class Expression *Unary::getExpression() { return this->expression; }

void Unary::setExpression(class Expression *expression) {
  this->expression = expression;
}

Binary::Binary(class Expression *left, class Token op,
               class Expression *right) {
  this->setType(Types::binary);
  this->left = left;
  this->setToken(op);
  this->right = right;
}

Binary::Binary() { this->setType(Types::binary); }

Binary::~Binary() {
  delete this->left;
  delete this->right;
}

class Expression *Binary::getLeft() { return this->left; }

void Binary::setLeft(class Expression *expression) { this->left = expression; }

class Expression *Binary::getRight() { return this->right; }

void Binary::setRight(class Expression *expression) {
  this->right = expression;
}

Ternary::Ternary(class Token op, class Expression *left,
                 class Expression *middle, class Expression *right) {
  this->setType(Types::ternary);
  this->setToken(op);
  this->setLeft(left);
  this->middle = middle;
  this->setRight(right);
}

Ternary::Ternary() { this->setType(Types::ternary); }

Ternary::~Ternary() { delete middle; }

class Expression *Ternary::getMiddle() { return this->middle; }

void Ternary::setMiddle(class Expression *middle) { this->middle = middle; }

Parenthesesed::Parenthesesed(class Token open, class Expression *expression,
                             class Token close) {
  this->setType(Types::parenthesised);
  this->open = open;
  this->setExpression(expression);
  this->close = close;
}

Parenthesesed::Parenthesesed() { this->setType(Types::parenthesised); }

Parenthesesed::~Parenthesesed() {}

class Token Parenthesesed::getOpen() { return this->open; }

void Parenthesesed::setOpen(class Token open) { this->open = open; }

class Token Parenthesesed::getClose() { return this->close; }

void Parenthesesed::setClose(class Token close) { this->close = close; }

String::String(class Token string) {
  this->setType(Types::string);
  this->setToken(string);
}

String::String() { this->setType(Types::string); }

String::~String() {}
}  // namespace Hash
