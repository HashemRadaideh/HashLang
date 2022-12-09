#include "evaluator.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "ast.hpp"
#include "token.hpp"
#include "types.hpp"

namespace Hash {
Evaluator::Evaluator(std::string& line, bool printTokens = false,
                     bool printTree = false)
    : parser(line, printTokens) {
  this->root = parser.getExpression();
  if (printTree) this->printTree();
}

Evaluator::~Evaluator() {
  // delete this->root;
}

int Evaluator::evaluation() { return eval(this->root); }

void Evaluator::printTree() {
  std::function<void(class Expression*, bool, std::string, std::string)> print;
  print = [&](class Expression* node, bool isLast = true,
              std::string indent = "", std::string branch = "") -> void {
    if (node == nullptr) return;

    branch = branch != "" ? isLast ? "└──" : "├──" : "";

    std::cout << indent << branch << "[" << parser.type(node->getType())
              << "] ";
    if (node->getType() != Types::parenthesised)
      std::cout << node->getValue().value << " ("
                << parser.type(node->getValue().type) << ")";
    std::cout << std::endl;

    indent += branch != "" ? isLast ? "   " : "│  " : "";
    branch = isLast ? "└──" : "├──";

    if (node->getType() == Types::unary) {
      print(((Unary*)node)->getExpression(), true, indent, branch);
    }

    if (node->getType() == Types::parenthesised) {
      Parenthesesed* paren = (Parenthesesed*)node;

      if (paren->getValue().value != "") {
        std::cout << indent << "├──"
                  << "(" << parser.type(paren->getValue().type) << ")  "
                  << paren->getValue().value << std::endl;
      }

      std::cout << indent << "├──"
                << "[" << parser.type(paren->getOpen().type) << "]  "
                << paren->getOpen().value << std::endl;

      print(paren->getExpression(), paren->getExpression() == nullptr, indent,
            branch);

      std::cout << indent << "└──"
                << "(" << parser.type(paren->getClose().type) << ") "
                << paren->getClose().value << std::endl;
    }

    if (node->getType() == Types::binary) {
      Binary* bin = (Binary*)node;
      print(bin->getLeft(), bin->getRight() == nullptr, indent, branch);
      print(bin->getRight(), true, indent, branch);
    }
  };

  print(this->root, true, "", "");
}

int Evaluator::eval(class Expression* node) {
  if (node->getType() == Types::number) {
    int number;
    std::stringstream(((Number*)node)->getValue().value) >> number;
    return number;
  }

  if (node->getType() == Types::boolean) {
    if (node->getValue().value == "true") return 1;
    return 0;
  }

  if (node->getType() == Types::unary) {
    Unary* uni = (Unary*)node;
    if (uni->getValue().type == Types::minus)
      return eval(uni->getExpression()) * -1;
    else if (uni->getValue().type == Types::bang)
      return !eval(uni->getExpression());
    return eval(uni->getExpression());
  }

  if (node->getType() == Types::binary) {
    Binary* bin = (Binary*)node;
    if (bin->getLeft()->getType() == Types::number &&
        bin->getRight()->getType() == Types::number) {
      int left = eval(bin->getLeft());
      int right = eval(bin->getRight());
      char op = bin->getValue().value[0];
      switch (op) {
        case '+':
          return left + right;

        case '-':
          return left - right;

        case '*':
          return left * right;

        case '/':
          return left / right;

        case '^':
          return pow(left, right);
      }
    }

    if (bin->getLeft()->getType() == Types::boolean &&
        bin->getRight()->getType() == Types::boolean) {
      bool left = eval(bin->getLeft());
      bool right = eval(bin->getRight());
      char op = bin->getValue().value[0];
      switch (op) {
        case '+':
          return left || right;

        case '*':
          return left && right;
      }
    }
  }

  if (node->getType() == Types::parenthesised) {
    int factor = 1;
    if (node->getValue().value != "") {
      class Expression* expr;
      if (node->getValue().type == Types::number) expr = new Number();
      expr->getValue() = node->getValue();
      factor = eval(expr);
    }
    return eval(((Parenthesesed*)node)->getExpression()) * factor;
  }

  return -1;
}

}  // namespace Hash
