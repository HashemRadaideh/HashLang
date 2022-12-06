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
      return Token(Types::eof);

    case ' ':
      return Token(Types::skip);

    case '\n':
      return Token(Types::skip);

    case '\t':
      return Token(Types::skip);

    case '+':
      return Token(Types::plus, "+", this->position - 1);

    case '-':
      return Token(Types::minus, "-", this->position - 1);

    case '=':
      return Token(Types::equal, "=", this->position - 1);

    case '*':
      return Token(Types::asterisk, "*", this->position - 1);

    case '/':
      return Token(Types::minus, "/", this->position - 1);

    case '\\':
      return Token(Types::minus, "\\", this->position - 1);
      break;

    case '(':
      return Token(Types::right_parenthesis, "(", this->position - 1);

    case ')':
      return Token(Types::left_parenthesis, ")", this->position - 1);

    case '"':
    case '`':
    case '\'': {
      char myQuote = this->current;
      struct Token token = Token();

      token.type = Types::string;
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

    token.type = Types::number;
    token.value = this->current;

    token.start = this->position - 1;
    while (isNumber(this->text[this->position])) {
      next();
      token.value += this->current;
    }
    token.end = this->position - 1;

    return token;
  }

  return Token();
}

bool Lexer::isNumber(char character) {
  return (character >= '0' && character <= '9');
}
}  // namespace HashLang
