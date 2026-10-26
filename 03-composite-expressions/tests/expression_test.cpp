#include "expr/add.hpp"
#include "expr/constant.hpp"
#include "expr/cos.hpp"
#include "expr/expression.hpp"
#include "expr/multiply.hpp"
#include "expr/power.hpp"
#include "expr/sin.hpp"
#include "expr/variable.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <vector>

TEST(ExpressionTest, ConstantAndVariable) {
    const auto c = std::make_shared<Constant>(5.0);
    EXPECT_DOUBLE_EQ(c->evaluate(10.0), 5.0);
    EXPECT_TRUE(c->asConstant().has_value());
    EXPECT_DOUBLE_EQ(*c->asConstant(), 5.0);

    const auto dc = c->derivative();
    EXPECT_DOUBLE_EQ(dc->evaluate(10.0), 0.0);

    const auto x = std::make_shared<Variable>();
    EXPECT_DOUBLE_EQ(x->evaluate(7.5), 7.5);
    EXPECT_FALSE(x->asConstant().has_value());

    const auto dx = x->derivative();
    EXPECT_DOUBLE_EQ(dx->evaluate(7.5), 1.0);
}

TEST(ExpressionTest, AddAndMultiply) {
    const auto x = std::make_shared<Variable>();
    const auto sum = std::make_shared<Add>(x, std::make_shared<Constant>(3.0));
    EXPECT_DOUBLE_EQ(sum->evaluate(4.0), 7.0);

    const auto dSum = sum->derivative();
    EXPECT_DOUBLE_EQ(dSum->evaluate(4.0), 1.0);

    const auto prod = std::make_shared<Multiply>(x, std::make_shared<Constant>(4.0));
    EXPECT_DOUBLE_EQ(prod->evaluate(3.0), 12.0);

    const auto dProd = prod->derivative();
    EXPECT_DOUBLE_EQ(dProd->evaluate(3.0), 4.0);
}

TEST(ExpressionTest, PowerRule) {
    const auto x = std::make_shared<Variable>();
    const auto xCubed = std::make_shared<Power>(x, std::make_shared<Constant>(3.0));
    EXPECT_DOUBLE_EQ(xCubed->evaluate(2.0), 8.0);

    const auto dPower = xCubed->derivative();
    // 3 * x^2 at x = 2 is 12
    EXPECT_DOUBLE_EQ(dPower->evaluate(2.0), 12.0);
}

TEST(ExpressionTest, TrigonometricFunctions) {
    const auto x = std::make_shared<Variable>();
    const auto sinX = std::make_shared<Sin>(x);
    const auto cosX = std::make_shared<Cos>(x);

    constexpr double val = 1.0;
    EXPECT_DOUBLE_EQ(sinX->evaluate(val), std::sin(val));
    EXPECT_DOUBLE_EQ(cosX->evaluate(val), std::cos(val));

    // d/dx sin(x) = cos(x)
    EXPECT_NEAR(sinX->derivative()->evaluate(val), std::cos(val), 1e-9);
    // d/dx cos(x) = -sin(x)
    EXPECT_NEAR(cosX->derivative()->evaluate(val), -std::sin(val), 1e-9);
}

TEST(ExpressionTest, NumericalVsSymbolicDerivativePropertyTest) {
    const auto x = std::make_shared<Variable>();
    // f(x) = (x^2 + 3x) * sin(x)
    const auto expr = std::make_shared<Multiply>(
        std::make_shared<Add>(
            std::make_shared<Power>(x, std::make_shared<Constant>(2.0)),
            std::make_shared<Multiply>(std::make_shared<Constant>(3.0), x)),
        std::make_shared<Sin>(x));

    const auto deriv = expr->derivative();

    // Verify f(2) = (4 + 6) * sin(2) ~ 9.092974268
    EXPECT_NEAR(expr->evaluate(2.0), 10.0 * std::sin(2.0), 1e-6);

    constexpr double h = 1e-6;
    const std::vector<double> testPoints = {0.5, 1.0, 1.5, 2.0, 2.5, 3.14159 / 2.0, 4.0};

    for (const double pt : testPoints) {
        const double fPlus = expr->evaluate(pt + h);
        const double fMinus = expr->evaluate(pt - h);
        const double numerical = (fPlus - fMinus) / (2.0 * h);
        const double symbolic = deriv->evaluate(pt);

        EXPECT_NEAR(symbolic, numerical, 1e-4)
            << "Mismatch at point x = " << pt << ": symbolic=" << symbolic
            << " numerical=" << numerical;
    }
}
