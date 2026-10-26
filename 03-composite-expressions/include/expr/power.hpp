#pragma once
#include "expr/constant.hpp"
#include "expr/expression.hpp"

class Power final : public Expression {
public:
    Power(ExprPtr base, std::shared_ptr<Constant> exponent);

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] ExprPtr derivative() const override;
    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] const ExprPtr& base() const noexcept;
    [[nodiscard]] const std::shared_ptr<Constant>& exponent() const noexcept;

private:
    ExprPtr base_;
    std::shared_ptr<Constant> exponent_;
};

[[nodiscard]] ExprPtr power(ExprPtr base, std::shared_ptr<Constant> exponent);
