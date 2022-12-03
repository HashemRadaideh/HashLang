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
    if (token.type != TokenType::eof)
      break;
    else if (token.type != TokenType::skip)
      this->tokens.emplace_back(token);
    this->nextCharacter();
  }
}

bool Lexer::isNumber(char character) {
  if (character >= '0' && character <= '9') return true;
  return false;
}

void Lexer::nextCharacter() {
  if (this->posistion >= text.length())
    this->current = '\0';
  else
    this->current = this->text[++this->posistion];
}
void Lexer::backCharacter() { this->current = this->text[--this->posistion]; }

Token Lexer::nextToken() {
  switch (this->current) {
    case '\0':
      return Token(TokenType::eof);

    case ' ':
      return Token(TokenType::skip);

    case '\n':
      return Token(TokenType::skip);

    case '\t':
      return Token(TokenType::skip);

    case '+':
      return Token(TokenType::plus, "+", this->posistion);

    case '-':
      return Token(TokenType::minus, "-", this->posistion);

    case '=':
      return Token(TokenType::equal, "=", this->posistion);

    case '*':
      return Token(TokenType::asterisk, "*", this->posistion);

    case '/':
      return Token(TokenType::minus, "/", this->posistion);

    case '\\':
      return Token(TokenType::minus, "\\", this->posistion);
      break;

    case '(':
      return Token(TokenType::right_parenthesis, "(", this->posistion);

    case ')':
      return Token(TokenType::left_parenthesis, ")", this->posistion);

    case '"':
    case '`':
    case '\'': {
      char myQuote = this->current;
      Token token = Token();
      token.type = TokenType::string;
      token.start = this->posistion + 1;

      do {
        this->nextCharacter();
      } while (this->current != myQuote);

      token.end = this->posistion - 1;
      token.value = this->text.substr(token.start, token.end);
      return token;
    }
  }

  if (isNumber(this->current)) {
    Token token = Token();
    token.type = TokenType::number;
    token.start = this->posistion;

    do {
      this->nextCharacter();
    } while (this->isNumber(this->current));
    this->backCharacter();

    token.end = this->posistion;
    token.value = this->text.substr(token.start, token.end + 1);
    return token;
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
}  // namespace HashLang
