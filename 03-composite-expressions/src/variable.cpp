#include "expr/variable.hpp"
#include "expr/constant.hpp"

double Variable::evaluate(double x) const {
    return x;
}

ExprPtr Variable::derivative() const {
    return std::make_shared<Constant>(1.0);
}

std::string Variable::toString() const {
    return "x";
}
