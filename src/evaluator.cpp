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
  if (printTree) this->printTree(this->root, true, "", "");
}

Evaluator::~Evaluator() {}  // delete this->root;

std::string Evaluator::evaluation() {
  enum Types type;
  if (this->root->getType() == Types::eof) return "";
  return std::to_string(eval(this->root, type));
}

void Evaluator::printTree(class Expression* node, bool isLast = true,
                          std::string indent = "", std::string branch = "") {
  if (node == nullptr) return;

  branch = branch != "" ? isLast ? "└──" : "├──" : "";

  std::cout << indent << branch << "[" << parser.type(node->getType()) << "] ";
  if (node->getType() != Types::parenthesised)
    std::cout << node->getValue().content << " ("
              << parser.type(node->getValue().type) << ")";
  std::cout << std::endl;

  indent += branch != "" ? isLast ? "   " : "│  " : "";
  branch = isLast ? "└──" : "├──";

  if (node->getType() == Types::unary) {
    printTree(((Unary*)node)->getExpression(), true, indent, branch);
  }

  if (node->getType() == Types::parenthesised) {
    Parenthesesed* paren = (Parenthesesed*)node;

    if (paren->getValue().content != "") {
      std::cout << indent << "├──"
                << "(" << parser.type(paren->getValue().type) << ")  "
                << paren->getValue().content << std::endl;
    }

    std::cout << indent << "├──"
              << "[" << parser.type(paren->getOpen().type) << "]  "
              << paren->getOpen().content << std::endl;

    printTree(paren->getExpression(), paren->getExpression() == nullptr, indent,
              branch);

    std::cout << indent << "└──"
              << "(" << parser.type(paren->getClose().type) << ") "
              << paren->getClose().content << std::endl;
  }

  if (node->getType() == Types::binary) {
    Binary* bin = (Binary*)node;
    printTree(bin->getLeft(), bin->getRight() == nullptr, indent, branch);
    printTree(bin->getRight(), true, indent, branch);
  }
}

int Evaluator::eval(class Expression* node, enum Types& type) {
  if (node->getType() == Types::number) {
    type = Types::number;
    int number;
    std::stringstream(((Number*)node)->getValue().content) >> number;
    return number;
  }

  if (node->getType() == Types::boolean) {
    type = Types::boolean;
    if (node->getValue().content == "true") return 1;
    return 0;
  }

  if (node->getType() == Types::unary) {
    Unary* uni = (Unary*)node;
    int number = eval(uni->getExpression(), type);
    if (type == Types::number) {
      if (uni->getValue().type == Types::minus) return number * -1;
      return number;
    } else if (type == Types::boolean) {
      if (uni->getValue().type == Types::bang) return !number;
    }
    return eval(uni->getExpression(), type);
  }

  if (node->getType() == Types::binary) {
    Binary* bin = (Binary*)node;

    int left = eval(bin->getLeft(), type);
    char op = bin->getValue().content[0];

    if (type == Types::boolean) {
      int right = eval(bin->getRight(), type);
      if (type == Types::boolean) {
        switch (op) {
          case '+':
            return left || right;

          case '*':
            return left && right;
        }
      }
    }

    if (type == Types::number) {
      int right = eval(bin->getRight(), type);
      if (type == Types::number) {
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
    }
  }

  if (node->getType() == Types::parenthesised) {
    int factor = 1;
    if (node->getValue().content != "") {
      class Expression* expr;
      if (node->getValue().type == Types::number) expr = new Number();
      expr->getValue() = node->getValue();
      factor = eval(expr, type);
    }
    return eval(((Parenthesesed*)node)->getExpression(), type) * factor;
  }

  return -1;
}

}  // namespace Hash
