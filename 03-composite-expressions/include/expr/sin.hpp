#pragma once
#include "expr/unary_function.hpp"

class Sin final : public UnaryFunction {
public:
    using UnaryFunction::UnaryFunction;

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] ExprPtr derivative() const override;
    [[nodiscard]] std::string toString() const override;
};
