#pragma once

#include "node.hpp"

namespace HashLang {
class Evaluator {
 public:
  Evaluator() = default;
  int eval(struct Node*);
};
}  // namespace HashLang