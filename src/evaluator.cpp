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
  if (printTree && this->root->getType() != Types::eof)
    this->printTree(this->root, true, "", "");
}

Evaluator::~Evaluator() {}  // delete this->root;

std::string Evaluator::evaluation() {
  enum Types type;
  if (this->root->getType() == Types::eof) return "";
  return std::to_string(eval(this->root));
}

int Evaluator::eval(class Expression* node) {
  if (node->getType() == Types::unary) {
    return getUnaryOperation((Unary*)node);
  }

  if (node->getType() == Types::binary) {
    return getBinaryOperation((Binary*)node);
  }

  if (node->getType() == Types::parenthesised) {
    int factor = 1;
    if (node->getToken().getContent() != "") {
      class Expression* expr;
      if (node->getToken().getType() == Types::number) expr = new Number();
      expr->getToken() = node->getToken();
      factor = eval(expr);
    }
    return eval(((Parenthesesed*)node)->getExpression()) * factor;
  }

  return -1;
}

int Evaluator::getUnaryOperation(Unary* uni) {
  enum Types type = getUnaryOperationType(uni->getExpression());

  if (type == Types::number) {
    int number = getNumber(uni->getExpression());
    if (uni->getToken().getType() == Types::minus) return number * -1;
    return number;
  } else if (type == Types::boolean) {
    int boolean = getBoolean(uni->getExpression());
    if (uni->getToken().getType() == Types::bang) return !boolean;
  }

  return eval(uni->getExpression());
}

int Evaluator::getBinaryOperation(Binary* bin) {
  enum Types type = getBinaryOperationType(bin->getLeft(), bin->getRight());

  if (type == Types::boolean) {
    bool left = getBoolean(bin->getLeft());
    bool right = getBoolean(bin->getRight());
    switch (bin->getToken().getContent()[0]) {
      case '+':
        return left || right;

      case '*':
        return left && right;
    }
  }

  if (type == Types::number) {
    int left = getNumber(bin->getLeft());
    int right = getNumber(bin->getRight());
    switch (bin->getToken().getContent()[0]) {
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

  // if (type == Types::string) {
  //   std::string left = getString(bin->getLeft());
  //   std::string right = getString(bin->getRight());
  //   switch (bin->getToken().getContent()[0]) {
  //     case '+':
  //       return left + right;
  //   }
  // }

  return -1;
}

enum Types Evaluator::getUnaryOperationType(Expression* node) {
  return node->getType();
}

enum Types Evaluator::getBinaryOperationType(class Expression* left,
                                             class Expression* right) {
  if (left->getType() != right->getType()) return Types::unkown;
  if (left->getType() == Types::string) return Types::string;
  if (left->getType() == Types::number) return Types::number;
  if (left->getType() == Types::boolean) return Types::boolean;
  return Types::unkown;
}

bool Evaluator::getBoolean(Expression* node) {
  return node->getToken().getContent() == "true";
}

int Evaluator::getNumber(Expression* node) {
  int number;
  std::stringstream(node->getToken().getContent()) >> number;
  return number;
}

std::string Evaluator::getString(Expression* node) {
  return node->getToken().getContent();
}

void Evaluator::printTree(class Expression* node, bool isLast = true,
                          std::string indent = "", std::string branch = "") {
  if (node == nullptr) return;

  branch = branch != "" ? isLast ? "└──" : "├──" : "";

  std::cout << indent << branch << "[" << Token::getTypeof(node->getType())
            << "] ";
  if (node->getType() != Types::parenthesised)
    std::cout << node->getToken().getContent() << " ("
              << Token::getTypeof(node->getToken().getType()) << ")";
  std::cout << std::endl;

  indent += branch != "" ? isLast ? "   " : "│  " : "";
  branch = isLast ? "└──" : "├──";

  if (node->getType() == Types::unary) {
    printTree(((Unary*)node)->getExpression(), true, indent, branch);
  }

  if (node->getType() == Types::parenthesised) {
    Parenthesesed* paren = (Parenthesesed*)node;

    if (paren->getToken().getContent() != "") {
      std::cout << indent << "├──"
                << "(" << Token::getTypeof(paren->getToken().getType()) << ")  "
                << paren->getToken().getContent() << std::endl;
    }

    std::cout << indent << "├──"
              << "[" << Token::getTypeof(paren->getOpen().getType()) << "]  "
              << paren->getOpen().getContent() << std::endl;

    printTree(paren->getExpression(), paren->getExpression() == nullptr, indent,
              branch);

    std::cout << indent << "└──"
              << "(" << Token::getTypeof(paren->getClose().getType()) << ") "
              << paren->getClose().getContent() << std::endl;
  }

  if (node->getType() == Types::binary) {
    Binary* bin = (Binary*)node;
    printTree(bin->getLeft(), bin->getRight() == nullptr, indent, branch);
    printTree(bin->getRight(), true, indent, branch);
  }
}
}  // namespace Hash
