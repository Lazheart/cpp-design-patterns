#include "expr/add.hpp"
#include "expr/constant.hpp"

#include <utility>

double Add::evaluate(double x) const {
    return lhs_->evaluate(x) + rhs_->evaluate(x);
}

ExprPtr Add::derivative() const {
    return add(lhs_->derivative(), rhs_->derivative());
}

std::string Add::toString() const {
    return "(" + lhs_->toString() + " + " + rhs_->toString() + ")";
}

ExprPtr add(ExprPtr a, ExprPtr b) {
    const auto ca = a->asConstant();
    const auto cb = b->asConstant();
    if (ca && *ca == 0.0) {
        return b;
    }
    if (cb && *cb == 0.0) {
        return a;
    }
    if (ca && cb) {
        return std::make_shared<Constant>(*ca + *cb);
    }
    return std::make_shared<Add>(std::move(a), std::move(b));
}
