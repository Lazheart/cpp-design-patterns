#pragma once
#include "expr/expression.hpp"

class BinaryOperation : public Expression {
public:
    BinaryOperation(ExprPtr lhs, ExprPtr rhs);

    [[nodiscard]] const ExprPtr& lhs() const noexcept;
    [[nodiscard]] const ExprPtr& rhs() const noexcept;

protected:
    ExprPtr lhs_;
    ExprPtr rhs_;
};
