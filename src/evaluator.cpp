#include "evaluator.hpp"

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "token.hpp"
#include "types.hpp"

namespace HashLang {
Evaluator::Evaluator(std::string& line) : parser(line) {
  this->root = parser.getExpression();
}

int Evaluator::evaluation() { return eval(this->root); }

void Evaluator::printTokens() {
  std::function<void(struct Node*)> print = [&](struct Node* node) -> void {
    if (node == nullptr) return;

    print(node->left);

    std::cout << "Token: " << tokenInfo(node->data.type)
              << "\nValue: " << node->data.value << "\nAt: " << node->data.start
              << " - " << node->data.end << std::endl;

    print(node->right);
  };

  print(this->root);
}

void Evaluator::printTree() {
  std::function<void(struct Node*, bool, std::string, std::string)> print =
      [&](struct Node* node, bool isLast = true, std::string indent = "",
          std::string branch = "") {
        if (node == nullptr) return;

        branch = branch != "" ? isLast ? "└──" : "├──" : "";
        std::cout << indent << branch << node->data.value << " ("
                  << tokenInfo(node->data.type) << ")\n";
        indent += branch != "" ? isLast ? "   " : "│  " : "";
        branch = isLast ? "└──" : "├──";

        print(node->left, node->right == nullptr, indent, branch);
        print(node->right, true, indent, branch);
      };

  print(this->root, true, "", "");
}

int Evaluator::eval(struct Node* node) {
  if (node->data.type == TokenType::number) {
    int number;
    std::stringstream(node->data.value) >> number;
    return number;
  }

  if (node->data.type == TokenType::plus ||
      node->data.type == TokenType::minus ||
      node->data.type == TokenType::asterisk ||
      node->data.type == TokenType::slash) {
    int left = eval(node->left);
    int right = eval(node->right);
    char op = node->data.value[0];
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

std::string Evaluator::tokenInfo(struct Token token) {
  if (token.type == TokenType::number)
    return "number literal";
  else if (token.type == TokenType::string)
    return "string literal";
  else if (token.type == TokenType::plus)
    return "plus sign";
  else if (token.type == TokenType::minus)
    return "minus sign";
  else if (token.type == TokenType::asterisk)
    return "asterisk";
  else if (token.type == TokenType::slash)
    return "forward slash";
  return "Unkown token type";
}
}  // namespace HashLang
