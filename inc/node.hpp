#pragma once

#include "token.hpp"

namespace HashLang {
struct Node {
  struct Token data;
  struct Node *left, *right;
  Node(struct Token data = Token(), struct Node *left = nullptr,
       struct Node *right = nullptr) {
    data = data;
    left = left;
    right = right;
  }
};
}  // namespace HashLang