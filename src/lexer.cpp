#include "lexer.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

namespace HashLang {
Lexer::Lexer(std::string text) {
  this->text = text;
  this->posistion = 0;
  this->current = this->text[this->posistion];
}

void Lexer::nextCharacter() {
  if (this->posistion >= text.length())
    this->current = '\0';
  else
    this->current = this->text[++this->posistion];
}

struct Token Lexer::nextToken() {
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
      struct Token token = Token();
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
    struct Token token = Token();
    token.type = TokenType::number;
    token.start = this->posistion;

    do {
      this->nextCharacter();
    } while (this->isNumber(this->text[this->posistion + 1]));

    token.end = this->posistion;
    token.value = this->text.substr(token.start, token.end + 1);
    return token;
  }

  return Token();
}

bool Lexer::isNumber(char character) {
  if (character >= '0' && character <= '9') return true;
  return false;
}
}  // namespace HashLang
