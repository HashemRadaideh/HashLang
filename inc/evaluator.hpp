#pragma once

#include "node.hpp"

namespace HashLang {
class Evaluator {
 public:
  Evaluator() = default;
  ~Evaluator() = default;
  int evaluate(struct Node*);
};
}  // namespace HashLang
