#include "evaluator.hpp"

#include <sstream>
#include <string>

#include "token.hpp"
#include "types.hpp"

namespace HashLang {
int Evaluator::evaluate(struct Node* root) {
  if (root->data.type == Types::number) {
    int n;
    std::stringstream(root->data.value) >> n;
    return n;
    // return std::atoi(root->data.value.c_str());
  }

  if (root->data.type == Types::plus || root->data.type == Types::minus ||
      root->data.type == Types::asterisk ||
      root->data.type == Types::forward_slash) {
    int left = evaluate(root->left);
    int right = evaluate(root->right);
    char op = root->data.value[0];
    switch (op) {
      case '+':
        return left + right;
      case '-':
        return left - right;
      case '*':
        return left * right;
      case '/':
        return left / right;
    }
  }

  return 0;
}
}  // namespace HashLang
