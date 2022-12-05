#include "evaluator.hpp"

#include <string>

#include "token.hpp"

namespace HashLang {
int Evaluator::eval(struct Node* root) {
  if (root->data.type == TokenType::number) {
    return std::atoi(root->data.value.c_str());
  }

  if (root->data.type == TokenType::plus ||
      root->data.type == TokenType::minus) {
    int left = eval(root->left);
    int right = eval(root->right);
    char op = root->data.value[0];
    switch (op) {
      case '+':
        return left + right;
      case '-':
        return left - right;
    }
  }
}
}  // namespace HashLang