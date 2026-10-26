#include "expr/multiply.hpp"
#include "expr/add.hpp"
#include "expr/constant.hpp"

#include <utility>

double Multiply::evaluate(double x) const {
    return lhs_->evaluate(x) * rhs_->evaluate(x);
}

ExprPtr Multiply::derivative() const {
    return add(multiply(lhs_->derivative(), rhs_), multiply(lhs_, rhs_->derivative()));
}

std::string Multiply::toString() const {
    return "(" + lhs_->toString() + " * " + rhs_->toString() + ")";
}

ExprPtr multiply(ExprPtr a, ExprPtr b) {
    const auto ca = a->asConstant();
    const auto cb = b->asConstant();
    if ((ca && *ca == 0.0) || (cb && *cb == 0.0)) {
        return std::make_shared<Constant>(0.0);
    }
    if (ca && *ca == 1.0) {
        return b;
    }
    if (cb && *cb == 1.0) {
        return a;
    }
    if (ca && cb) {
        return std::make_shared<Constant>(*ca * *cb);
    }
    return std::make_shared<Multiply>(std::move(a), std::move(b));
}
