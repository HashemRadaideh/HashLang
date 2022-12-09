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
  int eval(class Expression*, enum Types&);

 private:
  class Parser parser;
  class Expression* root;
};
}  // namespace Hash
