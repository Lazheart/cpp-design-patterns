#pragma once
#include "expr/expression.hpp"

class UnaryFunction : public Expression {
public:
    explicit UnaryFunction(ExprPtr arg);

    [[nodiscard]] const ExprPtr& arg() const noexcept;

protected:
    ExprPtr arg_;
};
