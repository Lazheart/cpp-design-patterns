#include "expr/sin.hpp"
#include "expr/cos.hpp"
#include "expr/multiply.hpp"

#include <cmath>

double Sin::evaluate(double x) const {
    return std::sin(arg_->evaluate(x));
}

ExprPtr Sin::derivative() const {
    return multiply(std::make_shared<Cos>(arg_), arg_->derivative());
}

std::string Sin::toString() const {
    return "sin(" + arg_->toString() + ")";
}
