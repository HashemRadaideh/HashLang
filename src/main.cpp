#include <iostream>
#include <string>

#include "lexer.hpp"

auto main(int argc, char *argv[]) -> int {
  while (true) {
    std::cout << "-> ";
    std::string line = "";
    std::getline(std::cin, line);
    if (line != "\0") {
      HashLang::Lexer lexer = HashLang::Lexer(line);
      lexer.printTokens();
    } else {
      std::cerr << "Input invalid\n";
    }
  }
  return 0;
}
