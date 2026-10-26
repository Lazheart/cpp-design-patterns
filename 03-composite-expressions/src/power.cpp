#include "expr/power.hpp"
#include "expr/multiply.hpp"

#include <cmath>
#include <utility>

Power::Power(ExprPtr base, std::shared_ptr<Constant> exponent)
    : base_(std::move(base)), exponent_(std::move(exponent)) {}

double Power::evaluate(double x) const {
    return std::pow(base_->evaluate(x), exponent_->value());
}

ExprPtr Power::derivative() const {
    const double n = exponent_->value();
    if (n == 0.0) {
        return std::make_shared<Constant>(0.0);
    }
    const auto nConst = std::make_shared<Constant>(n);
    if (n == 1.0) {
        return base_->derivative();
    }
    const auto nMinus1 = std::make_shared<Constant>(n - 1.0);
    const auto uPow = power(base_, nMinus1);
    return multiply(multiply(nConst, uPow), base_->derivative());
}

std::string Power::toString() const {
    return base_->toString() + "^" + exponent_->toString();
}

const ExprPtr& Power::base() const noexcept {
    return base_;
}

const std::shared_ptr<Constant>& Power::exponent() const noexcept {
    return exponent_;
}

ExprPtr power(ExprPtr base, std::shared_ptr<Constant> exponent) {
    if (exponent->value() == 0.0) {
        return std::make_shared<Constant>(1.0);
    }
    if (exponent->value() == 1.0) {
        return base;
    }
    if (const auto c = base->asConstant()) {
        return std::make_shared<Constant>(std::pow(*c, exponent->value()));
    }
    return std::make_shared<Power>(std::move(base), std::move(exponent));
}
