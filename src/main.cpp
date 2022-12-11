#include <fstream>
#include <iostream>
#include <string>

#include "evaluator.hpp"

static bool showTokens = false;
static bool showTree = true;

bool interpret(std::string line) {
  Hash::Evaluator evaluator = Hash::Evaluator(line, showTokens, showTree);
  if (evaluator.evaluation() != "") {
    std::cout << evaluator.evaluation() << std::endl;
    return 1;
  }
  return 0;
}

bool repl() {
  bool status = true;
  while (true) {
    std::cout << (status ? "#[]> " : "#[]> ");
    std::string line = "";
    std::getline(std::cin, line);

    if (line == "exit()") {
      exit(0);
    } else if (line == "#tree") {
      showTree = !showTree;
      continue;
    } else if (line == "#tokens") {
      showTokens = !showTokens;
      continue;
    }

    status = interpret(line);
  }
  return 1;
}

bool help(int status) {
  std::cout << R"(Usage: hash <flag> <file>
no options will launch interactive shell (repl) mode)"
            << std::endl;
  return status;
}

bool readFile(std::string fileName) {
  std::ifstream file = std::ifstream(fileName);

  if (file.fail()) {
    std::cerr << "File not found\n";
    return 1;
  }

  std::string line = "";
  while (std::getline(file, line)) interpret(line);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    return repl();
  else
    return readFile(argv[1]);
}
