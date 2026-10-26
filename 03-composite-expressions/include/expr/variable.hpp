#pragma once
#include "expr/expression.hpp"

class Variable final : public Expression {
public:
    Variable() = default;

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] ExprPtr derivative() const override;
    [[nodiscard]] std::string toString() const override;
};
