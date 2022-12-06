#include <string.h>

#include <fstream>
#include <iostream>
#include <string>

#include "evaluator.hpp"
#include "lexer.hpp"
#include "node.hpp"
#include "parser.hpp"
#include "token.hpp"

using evaluator = class HashLang::Evaluator;
using lexer = class HashLang::Lexer;
using node = struct HashLang::Node;
using parser = class HashLang::Parser;
using token = struct HashLang::Token;
using types = enum HashLang::Types;

static bool showTree = false;
static bool showTokens = false;

std::string tokenInfo(token tok) {
  if (tok.type == types::number)
    return "number literal";
  else if (tok.type == types::string)
    return "string literal";
  else if (tok.type == types::plus)
    return "plus sign";
  else if (tok.type == types::minus)
    return "minus sign";
  else if (tok.type == types::asterisk)
    return "asterisk";
  else if (tok.type == types::forward_slash)
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

void interpret(std::string line) {
  if (line == "exit()") {
    exit(0);
  } else if (line == "\0") {
    std::cerr << "Input invalid\n";
    return;
  } else if (line == "tree()") {
    showTree = !showTree;
    return;
  } else if (line == "tokens()") {
    showTokens = !showTokens;
    return;
  }

  parser par = parser(line);

  if (showTokens) printTokens(par.getTokens());
  if (showTree) printTree(par.getExpression());

  evaluator eval = evaluator();
  std::cout << eval.evaluate(par.getExpression()) << std::endl;
}

bool interactive() {
  while (true) {
    std::cout << "-> ";
    std::string line = "";
    std::getline(std::cin, line);
    interpret(line);
  }
  return 1;
}

bool help(int status) {
  std::cout << R"(Usage: hashlang <flag> <file_name>
no options will launch interactive shell mode)"
            << std::endl;
  return status;
}

bool read_file(char *file_name) {
  std::fstream file = std::fstream(file_name);

  if (file.fail()) {
    std::cerr << "File not found\n";
    return 1;
  }

  std::cout << "file is being read\n";
  std::string line = "";
  while (std::getline(file, line)) interpret(line);

  return 0;
}

auto main(int argc, char *argv[]) -> int {
  if (argc < 2) return interactive();
  for (int i = 1; i <= argc; i++)
    if (strcmp(argv[i], "--help") || strcmp(argv[i], "-h"))
      return help(0);
    else
      return read_file(argv[i]);

  return 0;
}
