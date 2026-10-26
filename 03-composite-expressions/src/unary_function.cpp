#include "expr/unary_function.hpp"

#include <utility>

UnaryFunction::UnaryFunction(ExprPtr arg) : arg_(std::move(arg)) {}

const ExprPtr& UnaryFunction::arg() const noexcept {
    return arg_;
}
