#include "ast.hpp"

#include "types.hpp"

namespace HashLang {
Expression::Expression() { this->type = Types::unkown; }

Expression::~Expression() {}

Number::Number() { this->type = Types::number; }

Number::~Number() {}

Binary::Binary() { this->type = Types::binary; }

Binary::~Binary() {
  delete this->left;
  delete this->right;
}

Parenthesesed::Parenthesesed() { this->type = Types::parenthesised; }

Parenthesesed::~Parenthesesed() { delete this->expression; }

Unary::Unary() { this->type = Types::unary; }

Unary::~Unary() { delete expression; }

Boolean::Boolean() { this->type = Types::boolean; }

Boolean::~Boolean() {}
}  // namespace HashLang
