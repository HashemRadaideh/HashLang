#pragma once

#include "token.hpp"
#include "types.hpp"

namespace Hash {
class Expression {
 public:
  Expression(enum Types, class Token);
  Expression();
  ~Expression();
  enum Types getType();
  void setType(enum Types);
  class Token getToken();
  void setToken(class Token);

 private:
  enum Types type;
  class Token token;
};

class Number : public Expression {
 public:
  Number(class Token);
  Number();
  ~Number();

 private:
};

class Boolean : public Expression {
 public:
  Boolean(class Token);
  Boolean();
  ~Boolean();

 private:
};

class String : public Expression {
 public:
  String(class Token);
  String();
  ~String();

 private:
};

class Unary : public Expression {
 public:
  Unary(class Token, class Expression *);
  Unary();
  ~Unary();
  class Expression *getExpression();
  void setExpression(class Expression *);

 private:
  class Expression *expression;
};

class Binary : public Expression {
 public:
  Binary(class Expression *, class Token, class Expression *);
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
  Ternary(class Token, class Expression *, class Expression *,
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
  Parenthesesed(class Token, class Expression *, class Token);
  Parenthesesed();
  ~Parenthesesed();
  class Token getOpen();
  void setOpen(class Token);
  class Token getClose();
  void setClose(class Token);

 private:
  class Token open;
  class Token close;
};
}  // namespace Hash
