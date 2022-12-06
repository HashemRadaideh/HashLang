#pragma once

#include "token.hpp"

namespace HashLang {
struct Node {
  struct Token data;
  struct Node *left, *right;
  Node() { left = right = nullptr; };
  Node(struct Token data, struct Node *left, struct Node *right) {
    data = data;
    left = left;
    right = right;
  };
  ~Node() = default;
};
}  // namespace HashLang
