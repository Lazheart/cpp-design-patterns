#include "expr/cos.hpp"
#include "expr/constant.hpp"
#include "expr/multiply.hpp"
#include "expr/sin.hpp"

#include <cmath>

double Cos::evaluate(double x) const {
    return std::cos(arg_->evaluate(x));
}

ExprPtr Cos::derivative() const {
    const auto minusOne = std::make_shared<Constant>(-1.0);
    const auto sinPart = std::make_shared<Sin>(arg_);
    return multiply(multiply(minusOne, sinPart), arg_->derivative());
}

std::string Cos::toString() const {
    return "cos(" + arg_->toString() + ")";
}
