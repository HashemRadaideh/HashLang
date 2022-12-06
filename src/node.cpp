#include "node.hpp"

#include "types.hpp"

namespace HashLang {
Expression::Expression() { this->type = Types::unkown; }

Expression::~Expression() {}

Number::Number() { this->type = Types::number; }

Number::~Number() {}

BinaryExpression::BinaryExpression() { this->type = Types::binary; }

BinaryExpression::~BinaryExpression() {
  delete left;
  delete right;
}
}  // namespace HashLang