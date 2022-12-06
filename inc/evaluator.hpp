#pragma once

#include "ast.hpp"
#include "parser.hpp"

namespace HashLang {
class Evaluator {
 public:
  Evaluator(std::string&);
  ~Evaluator() = default;
  int evaluation();
  void printTree();
  void printTokens();

 protected:
  std::string tokenInfo(enum Types);
  int eval(class Expression*);

 private:
  class Parser parser;
  class Expression* root;
};
}  // namespace HashLang
