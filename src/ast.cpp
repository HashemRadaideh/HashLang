#include "ast.hpp"

#include "types.hpp"

namespace HashLang {
Expression::Expression() { this->type = Types::unkown; }

Expression::~Expression() {}

Number::Number() { this->type = Types::number; }

Number::~Number() {}

BinaryExpression::BinaryExpression() { this->type = Types::binary; }

BinaryExpression::~BinaryExpression() {
  delete this->left;
  delete this->right;
}

ParenthesisedExpression::ParenthesisedExpression() {
  this->type = Types::parenthesised;
}

ParenthesisedExpression::~ParenthesisedExpression() { delete this->expression; }
}  // namespace HashLang