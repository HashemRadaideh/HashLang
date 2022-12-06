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
  int eval(struct Node*);

 private:
  class Parser parser;
  struct Node* root;
};
}  // namespace HashLang
