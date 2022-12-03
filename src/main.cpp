#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

using lexer = HashLang::Lexer;
using parser = HashLang::Parser;

auto main(int argc, char *argv[]) -> int {
  while (true) {
    std::cout << "-> ";
    std::string line = "";
    std::getline(std::cin, line);
    if (line != "\0") {
      // std::cout << line << std::endl;
      // lexer lex = lexer(line);
      // lex.printTokens();
      parser par = parser(line);
      par.printTree(par.getNodes(), "", true);
    } else {
      std::cerr << "Input invalid\n";
    }
  }
  return 0;
}
