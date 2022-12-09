#pragma once

#include "token.hpp"
#include "types.hpp"

namespace Hash {
class Expression {
 public:
  Expression(enum Types, struct Token);
  Expression();
  ~Expression();
  enum Types getType();
  void setType(enum Types);
  struct Token getValue();
  void getToken(struct Token);

 private:
  enum Types type;
  struct Token token;
};

class Number : public Expression {
 public:
  Number(struct Token);
  Number();
  ~Number();

 private:
};

class Boolean : public Expression {
 public:
  Boolean(struct Token);
  Boolean();
  ~Boolean();

 private:
};

class Unary : public Expression {
 public:
  Unary(struct Token, class Expression *);
  Unary();
  ~Unary();
  class Expression *getExpression();
  void setExpression(class Expression *);

 private:
  class Expression *expression;
};

class Binary : public Expression {
 public:
  Binary(class Expression *, struct Token, class Expression *);
  Binary();
  ~Binary();
  class Expression *getLeft();
  void setLeft(class Expression *);
  class Expression *getRight();
  void setRight(class Expression *);

 private:
  class Expression *left;
  class Expression *right;
};

class Ternary : public Binary {
 public:
  Ternary(struct Token, class Expression *, class Expression *,
          class Expression *);
  Ternary();
  ~Ternary();
  class Expression *getMiddle();
  void setMiddle(class Expression *);

 private:
  class Expression *middle;
};

class Parenthesesed : public Unary {
 public:
  Parenthesesed(struct Token, class Expression *, struct Token);
  Parenthesesed();
  ~Parenthesesed();
  struct Token getOpen();
  void setOpen(struct Token);
  struct Token getClose();
  void setClose(struct Token);

 private:
  struct Token open;
  struct Token close;
};
}  // namespace Hash
