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

class Token Lexer::getToken() {
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
      return Token(Types::plus, "+", this->position - 1, 0);

    case '-':
      return Token(Types::minus, "-", this->position - 1, 0);

    case '=':
      return Token(Types::equal, "=", this->position - 1, 0);

    case '*':
      return Token(Types::asterisk, "*", this->position - 1, 0);

    case '/':
      if (peek(0) == '/') {
        do {
          next();
        } while (this->current != '\n' && this->current != '\0');
        return Token(Types::skip);
      }
      return Token(Types::slash, "/", this->position - 1, 0);

    case '\\':
      return Token(Types::back_slash, "\\", this->position - 1, 0);

    case '^':
      return Token(Types::power, "^", this->position - 1, 0);

    case '!':
      return Token(Types::bang, "!", this->position - 1, 0);

    case '(':
      return Token(Types::open_parenthesis, "(", this->position - 1, 0);

    case ')':
      return Token(Types::close_parenthesis, ")", this->position - 1, 0);

    case '"':
    case '`':
    case '\'': {
      char myQuote = this->current;
      class Token token = Token();

      token.setType(Types::string);
      token.setStart(this->position);
      std::string str = "";
      do {
        next();
        str += this->current != myQuote ? this->current : '\0';
      } while (this->current != myQuote);
      next();
      token.setContent(str);
      token.setEnd(this->position - 1);

      return token;
    }
  }

  if (isNumber(this->current)) {
    class Token token = Token();

    token.setType(Types::number);

    std::string str = {this->current};

    token.setStart(this->position - 1);
    while (isNumber(peek(0))) {
      next();
      str += this->current;
    }
    token.setEnd(this->position - 1);

    token.setContent(str);

    return token;
  } else if (isAlpha(this->current) || this->current == '_') {
    class Token token = Token();

    std::string str = {this->current};

    token.setStart(this->position - 1);
    while (isAlpha(peek(0)) || isNumber(peek(0)) || peek(0) == '_') {
      next();
      str += this->current;
    }
    token.setEnd(this->position - 1);

    token.setContent(str);

    token = matcher(token);

    return token;
  }

  return Token();
}

class Token Lexer::matcher(class Token token) {
  if (token.getContent() == "true")
    token.setType(Types::boolean);
  else if (token.getContent() == "false")
    token.setType(Types::boolean);
  else if (token.getContent() == "if")
    token.setType(Types::keyword);
  else
    token.setType(Types::identifier);
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
