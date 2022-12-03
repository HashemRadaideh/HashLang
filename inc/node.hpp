#pragma once

#include "token.hpp"

namespace HashLang {
struct Node {
  struct Token data;
  struct Node *left, *right;
  Node() { left = right = nullptr; }
};
}  // namespace HashLang