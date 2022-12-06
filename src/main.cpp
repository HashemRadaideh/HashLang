#include <string.h>

#include <fstream>
#include <iostream>
#include <string>

#include "evaluator.hpp"
#include "lexer.hpp"
#include "node.hpp"
#include "parser.hpp"
#include "token.hpp"

static bool showTokens = false;
static bool showTree = false;

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

  HashLang::Evaluator evaluator = line;

  if (showTokens) evaluator.printTokens();
  if (showTree) evaluator.printTree();

  std::cout << evaluator.evaluation() << std::endl;
}

bool repl() {
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
no options will launch interactive shell (repl) mode)"
            << std::endl;
  return status;
}

bool read_file(char *file_name) {
  std::fstream file = std::fstream(file_name);

  if (file.fail()) {
    std::cerr << "File not found\n";
    return 1;
  }

  std::string line = "";
  while (std::getline(file, line)) interpret(line);

  return 0;
}

auto main(int argc, char *argv[]) -> int {
  if (argc < 2) return repl();
  for (int i = 1; i <= argc; i++)
    if (strcmp(argv[i], "--help") || strcmp(argv[i], "-h"))
      return help(0);
    else
      return read_file(argv[i]);

  return 0;
}
