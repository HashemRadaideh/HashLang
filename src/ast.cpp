#include "ast.hpp"

#include "types.hpp"

namespace Hash {
Expression::Expression(enum Types type, struct Token token) {
  this->type = type;
  this->token = token;
}

Expression::Expression() { this->type = Types::unkown; }

Expression::~Expression() {}

void Expression::setType(enum Types type) { this->type = type; }

enum Types Expression::getType() { return this->type; }

struct Token Expression::getValue() { return this->token; }

void Expression::setValue(struct Token token) { this->token = token; }

Number::Number(struct Token number) {
  this->setType(Types::number);
  this->setValue(number);
}

Number::Number() { this->setType(Types::number); }

Number::~Number() {}

Boolean::Boolean(struct Token boolean) {
  this->setType(Types::boolean);
  this->setValue(boolean);
}

Boolean::Boolean() { this->setType(Types::boolean); }

Boolean::~Boolean() {}

Unary::Unary(class Expression *expression) {
  this->setType(Types::unary);
  this->expression = expression;
}

Unary::Unary() { this->setType(Types::unary); }

Unary::~Unary() { delete expression; }

class Expression *Unary::getExpression() { return this->expression; }

void Unary::setExpression(class Expression *expression) {
  this->expression = expression;
}

Binary::Binary(class Expression *left, struct Token op,
               class Expression *right) {
  this->setType(Types::binary);
  this->left = left;
  this->setValue(op);
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

void Binary::setRight(class Expression *expression) { this->right = right; }

Ternary::Ternary(struct Token op, class Expression *left,
                 class Expression *middle, class Expression *right) {
  this->setType(Types::ternary);
  this->setValue(op);
  this->setLeft(left);
  this->middle = middle;
  this->setRight(right);
}

Ternary::Ternary() { this->setType(Types::ternary); }

Ternary::~Ternary() { delete middle; }

class Expression *Ternary::getMiddle() { return this->middle; }

void Ternary::setMiddle(class Expression *middle) { this->middle = middle; }

Parenthesesed::Parenthesesed(struct Token open, class Expression *expression,
                             struct Token close) {
  this->setType(Types::parenthesised);
  this->open = open;
  this->setExpression(expression);
  this->close = close;
}

Parenthesesed::Parenthesesed() { this->setType(Types::parenthesised); }

Parenthesesed::~Parenthesesed() {}

struct Token Parenthesesed::getOpen() { return this->open; }

void Parenthesesed::setOpen(struct Token open) { this->open = open; }

struct Token Parenthesesed::getClose() { return this->close; }

void Parenthesesed::setClose(struct Token close) { this->close = close; }
}  // namespace HashLang
