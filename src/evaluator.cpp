#include "evaluator.hpp"

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "node.hpp"
#include "token.hpp"
#include "types.hpp"

namespace HashLang {
Evaluator::Evaluator(std::string& line) : parser(line) {
  this->root = parser.getExpression();
}

int Evaluator::evaluation() { return eval(this->root); }

// void Evaluator::printTokens() {
//   std::function<void(class Expression*)> print =
//       [&](class Expression* node) -> void {
//     if (node == nullptr) return;
//     if (node->type == Types::binary) (BinaryExpression*)node;

//     print(node->left);

//     std::cout << "Token: " << tokenInfo(node->data.type)
//               << "\nValue: " << node->data.value << "\nAt: " <<
//               node->data.start
//               << " - " << node->data.end << std::endl;

//     print(node->right);
//   };

//   print(this->root);
// }

// void Evaluator::printTree() {
//   std::function<void(class Expression*, bool, std::string, std::string)>
//   print =
//       [&](class Expression* node, bool isLast = true, std::string indent =
//       "",
//           std::string branch = "") {
//         if (node == nullptr) return;
//         if (node->type == Types::binary) (BinaryExpression*)node;

//         branch = branch != "" ? isLast ? "└──" : "├──" : "";
//         std::cout << indent << branch << node->data.value << " ("
//                   << tokenInfo(node->data.type) << ")\n";
//         indent += branch != "" ? isLast ? "   " : "│  " : "";
//         branch = isLast ? "└──" : "├──";

//         print(node->left, node->right == nullptr, indent, branch);
//         print(node->right, true, indent, branch);
//       };

//   print(this->root, true, "", "");
// }

int Evaluator::eval(class Expression* node) {
  if (node->type == Types::number) {
    int number;
    std::stringstream(((Number*)node)->number.value) >> number;
    return number;
  }

  if (node->type == Types::binary) {
    auto bin = (BinaryExpression*)node;
    if (bin->op.type == Types::plus || bin->op.type == Types::minus ||
        bin->op.type == Types::asterisk || bin->op.type == Types::slash) {
      int left = eval(bin->left);
      int right = eval(bin->right);
      char op = bin->op.value[0];
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
  }

  return 0;
}

std::string Evaluator::tokenInfo(struct Token token) {
  if (token.type == Types::number)
    return "number literal";
  else if (token.type == Types::string)
    return "string literal";
  else if (token.type == Types::plus)
    return "plus sign";
  else if (token.type == Types::minus)
    return "minus sign";
  else if (token.type == Types::asterisk)
    return "asterisk";
  else if (token.type == Types::slash)
    return "forward slash";
  return "Unkown token type";
}
}  // namespace HashLang
