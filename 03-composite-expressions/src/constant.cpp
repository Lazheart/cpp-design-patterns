#include "expr/constant.hpp"

#include <cmath>
#include <sstream>

Constant::Constant(double value) : value_(value) {}

double Constant::evaluate([[maybe_unused]] double x) const {
    return value_;
}

ExprPtr Constant::derivative() const {
    return std::make_shared<Constant>(0.0);
}

std::string Constant::toString() const {
    if (value_ == std::floor(value_) && !std::isinf(value_) && !std::isnan(value_)) {
        return std::to_string(static_cast<long long>(value_));
    }
    std::ostringstream oss;
    oss << value_;
    return oss.str();
}

std::optional<double> Constant::asConstant() const {
    return value_;
}

double Constant::value() const noexcept {
    return value_;
}
