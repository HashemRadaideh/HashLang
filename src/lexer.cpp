#include "lexer.hpp"

#include <string>

#include "token.hpp"
#include "types.hpp"

namespace Hash {
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
      return Token(Types::slash, "/", this->position - 1);

    case '\\':
      return Token(Types::back_slash, "\\", this->position - 1);

    case '^':
      return Token(Types::power, "^", this->position - 1);

    case '!':
      return Token(Types::bang, "!", this->position - 1);

    case '(':
      return Token(Types::open_parenthesis, "(", this->position - 1);

    case ')':
      return Token(Types::close_parenthesis, ")", this->position - 1);

    case '"':
    case '`':
    case '\'': {
      char myQuote = this->current;
      struct Token token = Token();

      token.type = Types::string;
      token.start = this->position;
      do {
        next();
        token.content += this->current != myQuote ? this->current : '\0';
      } while (this->current != myQuote);
      token.end = this->position - 1;

      return token;
    }
  }

  if (isNumber(this->current)) {
    struct Token token = Token();

    token.type = Types::number;
    token.content = this->current;

    token.start = this->position - 1;
    while (isNumber(peek(0))) {
      next();
      token.content += this->current;
    }
    token.end = this->position - 1;

    return token;
  } else if (isAlpha(this->current) || this->current == '_') {
    struct Token token = Token();

    token.content = this->current;
    token.start = this->position - 1;
    while (isAlpha(peek(0)) || isNumber(peek(0)) || peek(0) == '_') {
      next();
      token.content += this->current;
    }
    token.end = this->position - 1;

    token = matcher(token);

    return token;
  }

  return Token();
}

struct Token Lexer::matcher(struct Token token) {
  if (token.content == "true")
    token.type = Types::boolean;
  else if (token.content == "false")
    token.type = Types::boolean;
  else if (token.content == "if")
    token.type = Types::keyword;
  else
    token.type = Types::identifier;
  return token;
}

char Lexer::peek(int index = 0) { return this->text[this->position + index]; }

bool Lexer::isNumber(char character) {
  return character >= '0' && character <= '9';
}

bool Lexer::isAlpha(char character) {
  return (character == '_') || (character >= 'A' && character <= 'Z') ||
         (character >= 'a' && character <= 'z');
}
}  // namespace Hash
