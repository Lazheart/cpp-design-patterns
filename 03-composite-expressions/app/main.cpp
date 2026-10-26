#include "expr/add.hpp"
#include "expr/constant.hpp"
#include "expr/cos.hpp"
#include "expr/expression.hpp"
#include "expr/multiply.hpp"
#include "expr/power.hpp"
#include "expr/sin.hpp"
#include "expr/variable.hpp"

#include <iostream>
#include <memory>

int main() {
    auto x = std::make_shared<Variable>();
    auto expr = std::make_shared<Multiply>(
        std::make_shared<Add>(
            std::make_shared<Power>(x, std::make_shared<Constant>(2.0)),
            std::make_shared<Multiply>(std::make_shared<Constant>(3.0), x)),
        std::make_shared<Sin>(x));

    auto deriv = expr->derivative();

    std::cout << "f(x)  = " << expr->toString() << '\n';
    std::cout << "f'(x) = " << deriv->toString() << '\n';
    std::cout << "f(2)  = " << expr->evaluate(2.0) << '\n';

    return 0;
}
