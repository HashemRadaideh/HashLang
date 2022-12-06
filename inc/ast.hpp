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

class BinaryExpression : public Expression {
 public:
  BinaryExpression();
  ~BinaryExpression();

  class Expression *left;
  class Expression *right;
};

class ParenthesisedExpression : public Expression {
 public:
  ParenthesisedExpression();
  ~ParenthesisedExpression();

  struct Token open;
  class BinaryExpression *expression;
  struct Token close;
};
}  // namespace HashLang
