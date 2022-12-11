#pragma once

#include "ast.hpp"
#include "parser.hpp"

namespace Hash {
class Evaluator {
 public:
  Evaluator(std::string&, bool, bool);
  ~Evaluator();
  std::string evaluation();

 protected:
  void printTree(class Expression*, bool, std::string, std::string);
  int eval(class Expression*);
  int getUnaryOperation(class Unary*);
  enum Types getUnaryOperationType(class Expression*);
  int getBinaryOperation(class Binary*);
  enum Types getBinaryOperationType(class Expression*, class Expression*);
  bool getBoolean(class Expression*);
  int getNumber(class Expression*);
  std::string getString(class Expression*);

 private:
  class Parser parser;
  class Expression* root;
};
}  // namespace Hash
