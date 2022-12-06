#pragma once

#include "token.hpp"
#include "types.hpp"

namespace HashLang {
class Expression {
 public:
  Expression();
  ~Expression();

  enum Types type;
};

class Number : public Expression {
 public:
  Number();
  ~Number();

  struct Token number;
};

class BinaryExpression : public Expression {
 public:
  BinaryExpression();
  ~BinaryExpression();

  class Expression *left;
  struct Token op;
  class Expression *right;
};
}  // namespace HashLang
