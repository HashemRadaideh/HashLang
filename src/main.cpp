#include <iostream>
#include <string>

#include "lexer.hpp"
#include "node.hpp"
#include "parser.hpp"
#include "token.hpp"

using lexer = class HashLang::Lexer;
using node = struct HashLang::Node;
using parser = class HashLang::Parser;
using token = struct HashLang::Token;
using tokenType = enum HashLang::TokenType;

std::string tokenInfo(token tok) {
  if (tok.type == tokenType::number)
    return "number literal";
  else if (tok.type == tokenType::string)
    return "string literal";
  else if (tok.type == tokenType::plus)
    return "plus sign";
  else if (tok.type == tokenType::minus)
    return "minus sign";
  else if (tok.type == tokenType::asterisk)
    return "asterisk";
  else if (tok.type == tokenType::forward_slash)
    return "forward slash";
  return "Unkown token type";
}

void printTokens(std::vector<token> tokens) {
  for (token tok : tokens) {
    std::cout << "Token: " << tokenInfo(tok.type) << "\nValue: " << tok.value
              << "\nAt: " << tok.start << " - " << tok.end << std::endl;
  }
}

void printTree(node *node, bool isLast = true, std::string indent = "",
               std::string branch = "") {
  if (node == nullptr) return;

  branch = branch != "" ? isLast ? "└──" : "├──" : "";
  std::cout << indent << branch << node->data.value << " ("
            << tokenInfo(node->data.type) << ")\n";
  indent += branch != "" ? isLast ? "   " : "│  " : "";
  branch = isLast ? "└──" : "├──";

  printTree(node->left, node->right == nullptr, indent, branch);
  printTree(node->right, true, indent, branch);
}

auto main(int argc, char *argv[]) -> int {
  while (true) {
    std::cout << "-> ";
    std::string line = "";
    std::getline(std::cin, line);
    if (line != "\0") {
      parser par = parser(line);
      // printTokens(par.getTokens());
      node n = par.getNode();
      node *nod = &n;
      printTree(nod);
    } else {
      std::cerr << "Input invalid\n";
    }
  }
  return 0;
}
