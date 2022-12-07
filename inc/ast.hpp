#pragma once

#include "token.hpp"
#include "types.hpp"

namespace HashLang {
class Expression {
 public:
  Expression();
  ~Expression();

  struct Token value;
  enum Types type;
};

class Number : public Expression {
 public:
  Number();
  ~Number();
};

class Unary : public Expression {
 public:
  Unary();
  ~Unary();

  class Expression *expression;
};

class Binary : public Expression {
 public:
  Binary();
  ~Binary();

  class Expression *left;
  class Expression *right;
};

class Parenthesesed : public Expression {
 public:
  Parenthesesed();
  ~Parenthesesed();

  struct Token open;
  class Expression *expression;
  struct Token close;
};
}  // namespace HashLang
