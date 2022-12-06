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

void Evaluator::printTokens() {
  std::function<void(class Expression*)> print =
      [&](class Expression* node) -> void {
    if (node == nullptr) return;

    if (node->type == Types::binary) {
      auto bin = (BinaryExpression*)node;
      print(bin->left);
    }

    std::cout << "Token: " << tokenInfo(node->value.type)
              << "\nValue: " << node->value.value
              << "\nAt: " << node->value.start << " - " << node->value.end
              << std::endl;

    if (node->type == Types::binary) {
      print(((BinaryExpression*)node)->right);
    }
  };

  print(this->root);
}

void Evaluator::printTree() {
  std::function<void(class Expression*, bool, std::string, std::string)> print =
      [&](class Expression* node, bool isLast = true, std::string indent = "",
          std::string branch = "") -> void {
    if (node == nullptr) return;

    branch = branch != "" ? isLast ? "└──" : "├──" : "";

    std::cout << indent << branch << "<" << tokenInfo(node->type) << "> ";
    if (node->type != Types::parenthesised) std::cout << node->value.value;
    std::cout << std::endl;

    indent += branch != "" ? isLast ? "   " : "│  " : "";
    branch = isLast ? "└──" : "├──";

    if (node->type == Types::parenthesised) {
      auto bin = ((ParenthesisedExpression*)node)->expression;

      branch = branch != "" ? isLast ? "└──" : "├──" : "";

      std::cout << indent << branch << "<" << tokenInfo(node->value.type)
                << "> " << node->value.value << std::endl;

      std::cout << indent << branch << "<" << tokenInfo(bin->type) << "> ";
      if (bin->type != Types::parenthesised) std::cout << bin->value.value;
      std::cout << std::endl;

      indent += branch != "" ? isLast ? "   " : "│  " : "";
      branch = isLast ? "└──" : "├──";

      print(bin->left, bin->right == nullptr, indent, branch);
      print(bin->right, true, indent, branch);

      auto paren = (ParenthesisedExpression*)node;
      indent.resize(indent.size() - 5);
      std::cout << indent << "└──"
                << "<" << tokenInfo(paren->close.type) << "> "
                << paren->close.value << std::endl;
    }

    if (node->type == Types::binary) {
      auto bin = (BinaryExpression*)node;
      print(bin->left, bin->right == nullptr, indent, branch);
      print(bin->right, true, indent, branch);
    }
  };

  print(this->root, true, "", "");
}

int Evaluator::eval(class Expression* node) {
  if (node->type == Types::number) {
    int number;
    std::stringstream(((Number*)node)->value.value) >> number;
    return number;
  }

  if (node->type == Types::binary) {
    auto bin = (BinaryExpression*)node;
    if (bin->value.type == Types::plus || bin->value.type == Types::minus ||
        bin->value.type == Types::asterisk || bin->value.type == Types::slash) {
      int left = eval(bin->left);
      int right = eval(bin->right);
      char op = bin->value.value[0];
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

  if (node->type == Types::parenthesised) {
    return eval(((ParenthesisedExpression*)node)->expression);
  }

  return 0;
}

std::string Evaluator::tokenInfo(enum Types type) {
  if (type == Types::number)
    return "number literal";
  else if (type == Types::string)
    return "string literal";
  else if (type == Types::plus)
    return "plus sign";
  else if (type == Types::minus)
    return "minus sign";
  else if (type == Types::asterisk)
    return "asterisk";
  else if (type == Types::binary)
    return "binary expression";
  else if (type == Types::unary)
    return "unary expression";
  else if (type == Types::open_parenthesis)
    return "open parenthesis";
  else if (type == Types::close_parenthesis)
    return "close parenthesis";
  else if (type == Types::parenthesised)
    return "parenthesised expression";
  return "Unkown token type";
}
}  // namespace HashLang
