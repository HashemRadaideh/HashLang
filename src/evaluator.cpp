#include "evaluator.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "ast.hpp"
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
      Binary* bin = (Binary*)node;
      print(bin->left);
    }

    std::cout << "Token: " << type(node->token.type) << std::endl
              << "Value: " << node->token.value << std::endl
              << "At: " << node->token.start << " - " << node->token.end
              << std::endl;

    if (node->type == Types::binary) {
      print(((Binary*)node)->right);
    }
  };

  print(this->root);
}

void Evaluator::printTree() {
  std::function<void(class Expression*, bool, std::string, std::string)> print;
  print = [&](class Expression* node, bool isLast = true,
              std::string indent = "", std::string branch = "") -> void {
    if (node == nullptr) return;

    branch = branch != "" ? isLast ? "└──" : "├──" : "";

    std::cout << indent << branch << "[" << type(node->type) << "] ";
    if (node->type != Types::parenthesised)
      std::cout << node->token.value << " (" << type(node->token.type) << ")";
    std::cout << std::endl;

    indent += branch != "" ? isLast ? "   " : "│  " : "";
    branch = isLast ? "└──" : "├──";

    if (node->type == Types::unary) {
      print(((Unary*)node)->expression, true, indent, branch);
    }

    if (node->type == Types::parenthesised) {
      Parenthesesed* paren = (Parenthesesed*)node;

      if (paren->token.value != "") {
        std::cout << indent << "├──"
                  << "(" << type(paren->token.type) << ")  "
                  << paren->token.value << std::endl;
      }

      std::cout << indent << "├──"
                << "[" << type(paren->open.type) << "]  " << paren->open.value
                << std::endl;

      print(paren->expression, paren->expression == nullptr, indent, branch);

      std::cout << indent << "└──"
                << "(" << type(paren->close.type) << ") " << paren->close.value
                << std::endl;
    }

    if (node->type == Types::binary) {
      Binary* bin = (Binary*)node;
      print(bin->left, bin->right == nullptr, indent, branch);
      print(bin->right, true, indent, branch);
    }
  };

  print(this->root, true, "", "");
}

int Evaluator::eval(class Expression* node) {
  if (node->type == Types::number) {
    int number;
    std::stringstream(((Number*)node)->token.value) >> number;
    return number;
  }

  if (node->type == Types::boolean) {
    if (node->token.value == "true") return 1;
    return 0;
  }

  if (node->type == Types::unary) {
    Unary* uni = (Unary*)node;
    if (uni->token.type == Types::minus)
      return eval(uni->expression) * -1;
    else if (uni->token.type == Types::bang)
      return !eval(uni->expression);
    return eval(uni->expression);
  }

  if (node->type == Types::binary) {
    Binary* bin = (Binary*)node;
    if (bin->left->type == Types::number && bin->right->type == Types::number) {
      int left = eval(bin->left);
      int right = eval(bin->right);
      char op = bin->token.value[0];
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

    if (bin->left->type == Types::boolean &&
        bin->right->type == Types::boolean) {
      bool left = eval(bin->left);
      bool right = eval(bin->right);
      char op = bin->token.value[0];
      switch (op) {
        case '+':
          return left || right;

        case '*':
          return left && right;
      }
    }
  }

  if (node->type == Types::parenthesised) {
    int factor = 1;
    if (node->token.value != "") {
      class Expression* expr;
      if (node->token.type == Types::number) expr = new Number();
      expr->token = node->token;
      factor = eval(expr);
    }
    return eval(((Parenthesesed*)node)->expression) * factor;
  }

  return -1;
}

std::string Evaluator::type(enum Types type) {
  if (type == Types::number)
    return "number literal";
  else if (type == Types::string)
    return "string literal";
  else if (type == Types::boolean)
    return "boolean literal";
  else if (type == Types::plus)
    return "plus operator";
  else if (type == Types::minus)
    return "minus operator";
  else if (type == Types::asterisk)
    return "asterisk operator";
  else if (type == Types::bang)
    return "bang operator";
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
