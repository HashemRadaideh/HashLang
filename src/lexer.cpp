#include "lexer.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"
#include "types.hpp"

namespace HashLang {
Lexer::Lexer(std::string &text) {
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
      return Token(TokenType::slash, "/", this->position - 1);

    case '\\':
      return Token(TokenType::back_slash, "\\", this->position - 1);

    case '(':
      return Token(TokenType::open_parenthesis, "(", this->position - 1);

    case ')':
      return Token(TokenType::close_parenthesis, ")", this->position - 1);

    case '"':
    case '`':
    case '\'': {
      char myQuote = this->current;
      struct Token token = Token();

      token.type = TokenType::string;
      token.start = this->position;
      do {
        next();
        token.value += this->current != myQuote ? this->current : '\0';
      } while (this->current != myQuote);
      token.end = this->position - 1;

      return token;
    }
  }

  if (isNumber(this->current)) {
    struct Token token = Token();

    token.type = TokenType::number;
    token.value = this->current;

    token.start = this->position - 1;
    while (isNumber(peek(0))) {
      next();
      token.value += this->current;
    }
    token.end = this->position - 1;

    return token;
  } else if (isAlpha(this->current)) {
    struct Token token = Token();

    token.type = TokenType::identifier;
    token.value = this->current;

    token.start = this->position - 1;
    while (isAlpha(peek(0)) || isNumber(peek(0)) || peek(0) == '_') {
      next();
      token.value += this->current;
    }
    token.end = this->position - 1;

    return token;
  }

  return Token();
}

char Lexer::peek(int index = 0) { return this->text[this->position + index]; }

bool Lexer::isNumber(char character) {
  return (character >= '0' && character <= '9');
}

bool Lexer::isAlpha(char character) {
  return (character >= 'a' && character <= 'z');
}
}  // namespace HashLang
