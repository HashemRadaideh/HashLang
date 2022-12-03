#include "lexer.hpp"

#include <iostream>
#include <vector>

#include "token.hpp"

namespace HashLang {
Lexer::Lexer(std::string text) {
  this->tokens = std::vector<Token>();
  this->text = text;
  this->posistion = 0;
  this->current = this->text[this->posistion];

  while (this->current != '\0') {
    Token token = nextToken();
    if (token.type != TokenType::skip)
      tokens.emplace_back(token);
    nextCharacter();
  }
}

bool Lexer::isNumber(char character) {
  if (current >= '0' && current <= '9')
    return true;
  return false;
}

void Lexer::nextCharacter() {
  if (this->posistion <= text.length())
    this->current = this->text[this->posistion++];
  else
    this->current = '\0';
}
void Lexer::backCharacter() { this->current = this->text[--this->posistion]; }

Token Lexer::nextToken() {
  switch (this->current) {
  case ' ':
    return Token(TokenType::skip);
    break;

  case '\n':
    return Token(TokenType::skip);
    break;

  case '\t':
    return Token(TokenType::skip);
    break;

  case '+':
    return Token(TokenType::plus, "+", this->posistion - 1);
    break;

  case '-':
    return Token(TokenType::minus, "-", this->posistion - 1);
    break;

  case '=':
    return Token(TokenType::equal, "=", this->posistion - 1);
    break;

  case '*':
    return Token(TokenType::asterisk, "*", this->posistion - 1);
    break;

  case '/':
    return Token(TokenType::minus, "/", this->posistion - 1);
    break;

  case '\\':
    return Token(TokenType::minus, "\\", this->posistion - 1);
    break;

  case '(':
    return Token(TokenType::right_parenthesis, "(", this->posistion - 1);
    break;

  case ')':
    return Token(TokenType::left_parenthesis, ")", this->posistion - 1);
    break;

  default:
    if (isNumber(this->current)) {
      Token token = Token();
      token.type = TokenType::number;
      token.start = (!this->posistion) ? this->posistion : this->posistion - 1;

      do {
        nextCharacter();
      } while (isNumber(this->current));
      backCharacter();

      token.end = this->posistion - 1;
      token.value = text.substr(token.start, token.end + 1);
      return token;
    }
  }

  return Token();
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
} // namespace HashLang
