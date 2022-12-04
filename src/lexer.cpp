#include "lexer.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

namespace HashLang {
Lexer::Lexer(std::string text) {
  this->text = text;
  this->position = 0;
  this->current = this->text[this->position++];
}

void Lexer::next() {
  if (this->position >= text.length())
    this->current = '\0';
  else
    this->current = this->text[this->position++];
}

struct Token Lexer::getToken() {
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
      return Token(TokenType::plus, "+", this->position - 1);

    case '-':
      return Token(TokenType::minus, "-", this->position - 1);

    case '=':
      return Token(TokenType::equal, "=", this->position - 1);

    case '*':
      return Token(TokenType::asterisk, "*", this->position - 1);

    case '/':
      return Token(TokenType::minus, "/", this->position - 1);

    case '\\':
      return Token(TokenType::minus, "\\", this->position - 1);
      break;

    case '(':
      return Token(TokenType::right_parenthesis, "(", this->position - 1);

    case ')':
      return Token(TokenType::left_parenthesis, ")", this->position - 1);

    case '"':
    case '`':
    case '\'': {
      char myQuote = this->current;
      struct Token token = Token();
      token.type = TokenType::string;
      token.start = this->position + 1;

      do {
        this->next();
      } while (this->current != myQuote);

      token.end = this->position - 1;
      token.value = this->text.substr(token.start, token.end);
      return token;
    }
  }

  if (isNumber(this->current)) {
    struct Token token = Token();
    token.type = TokenType::number;
    token.start = this->position - 1;

    while (isNumber(this->text[this->position + 1])) {
      this->next();
    }

    token.end = this->position - 1;
    token.value = this->text.substr(token.start, token.end + 1);
    return token;
  }

  return Token();
}

bool Lexer::isNumber(char character) {
  return (character >= '0' && character <= '9');
}
}  // namespace HashLang
