#pragma once
#include "expr/expression.hpp"

class Constant final : public Expression {
public:
    explicit Constant(double value);

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] ExprPtr derivative() const override;
    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] std::optional<double> asConstant() const override;
    [[nodiscard]] double value() const noexcept;

private:
    double value_;
};
