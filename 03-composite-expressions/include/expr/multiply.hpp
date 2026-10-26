#pragma once
#include "expr/binary_operation.hpp"

class Multiply final : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] ExprPtr derivative() const override;
    [[nodiscard]] std::string toString() const override;
};

[[nodiscard]] ExprPtr multiply(ExprPtr a, ExprPtr b);
