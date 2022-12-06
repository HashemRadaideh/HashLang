#pragma once

#include "node.hpp"
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
  std::string tokenInfo(struct Token);
  int eval(class Expression*);

 private:
  class Parser parser;
  class Expression* root;
};
}  // namespace HashLang
