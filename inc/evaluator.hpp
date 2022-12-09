#pragma once

#include "ast.hpp"
#include "parser.hpp"

namespace Hash {
class Evaluator {
 public:
  Evaluator(std::string&, bool, bool);
  ~Evaluator();
  int evaluation();

 protected:
  void printTree();
  int eval(class Expression*);

 private:
  class Parser parser;
  class Expression* root;
};
}  // namespace Hash
