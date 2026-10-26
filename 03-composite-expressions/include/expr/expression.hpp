#pragma once
#include <memory>
#include <optional>
#include <string>

class Expression;
using ExprPtr = std::shared_ptr<Expression>;

class Expression {
public:
    virtual ~Expression() = default;
    [[nodiscard]] virtual double evaluate(double x) const = 0;
    [[nodiscard]] virtual ExprPtr derivative() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual std::optional<double> asConstant() const {
        return std::nullopt;
    }
};
