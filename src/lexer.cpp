#include "lexer.hpp"

#include <iostream>
#include <vector>

#include "token.hpp"

namespace HashLang {
Lexer::Lexer(std::string text) {
  this->tokens = std::vector<Token>();
  this->text = text;
  this->posistion = 0;
  this->current = this->text[++this->posistion];

  while (this->current != '\0') {
    nextToken();
  }
}

bool Lexer::isNumber(char character) {
  if (current >= '0' && current <= '9' || current == '.') return true;
  return false;
}

void Lexer::nextCharacter() {
  if (this->posistion <= text.length())
    this->current = this->text[this->posistion++];
  else
    this->current = '\0';
}

void Lexer::nextToken() {
  switch (this->current) {
    case ' ':
      nextCharacter();
      nextToken();
      break;

    case '\n':
      nextCharacter();
      nextToken();
      break;

    case '\t':
      nextCharacter();
      nextToken();
      break;

    case '+':
      tokens.emplace_back(Token(TokenType::plus, "+", this->posistion));
      nextCharacter();
      break;

    case '-':
      tokens.emplace_back(Token(TokenType::minus, "-", this->posistion));
      nextCharacter();
      break;

    case '=':
      tokens.emplace_back(Token(TokenType::equal, "=", this->posistion));
      nextCharacter();
      break;

    case '*':
      tokens.emplace_back(Token(TokenType::asterisk, "*", this->posistion));
      nextCharacter();
      break;

    case '/':
      tokens.emplace_back(Token(TokenType::minus, "/", this->posistion));
      nextCharacter();
      break;

    case '\\':
      tokens.emplace_back(Token(TokenType::minus, "\\", this->posistion));
      nextCharacter();
      break;

    case '(':
      tokens.emplace_back(
          Token(TokenType::right_parenthesis, "(", this->posistion));
      nextCharacter();
      break;

    case ')':
      tokens.emplace_back(
          Token(TokenType::left_parenthesis, ")", this->posistion));
      nextCharacter();
      break;

    default:
      if (isNumber(this->current)) {
        Token token = Token();
        token.type = TokenType::number;
        token.start = this->posistion;

        while (isNumber(this->current)) nextCharacter();

        token.end = this->posistion;

        token.value = text.substr(token.start - 1, token.end + 1);
        tokens.emplace_back(token);
      }
  }
}

void Lexer::printTokens() {
  for (Token token : this->tokens) {
    if (token.type == TokenType::number)
      std::cout << "Token: number literal";
    else if (token.type == TokenType::string)
      std::cout << "Token: string literal";
    else if (token.type == TokenType::plus)
      std::cout << "Token: plus sign";
    else if (token.type == TokenType::minus)
      std::cout << "Token: minus sign";
    else if (token.type == TokenType::asterisk)
      std::cout << "Token: asterisk";
    else if (token.type == TokenType::forward_slash)
      std::cout << "Token: forward slash";
    else
      std::cerr << "Unkown token type";

    std::cout << "\nValue: " << token.value << "\nAt: " << token.start << " - "
              << token.end << std::endl;
  }
}
}  // namespace HashLang
