#include "expr/binary_operation.hpp"

#include <utility>

BinaryOperation::BinaryOperation(ExprPtr lhs, ExprPtr rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

const ExprPtr& BinaryOperation::lhs() const noexcept {
    return lhs_;
}

const ExprPtr& BinaryOperation::rhs() const noexcept {
    return rhs_;
}
