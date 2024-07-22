#ifndef EXPRTKENGINE_H
#define EXPRTKENGINE_H

#include <exprtk/exprtk.hpp>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QException>
#include <QtTypes>

#include <cmath>
#include <numbers>

#include "dice_roll.h"
#include "exprtk_methods.hpp"

class ExprTkEngine
{
public:
    ExprTkEngine();

    long double evaluate(const QString& expression);

    void setDiceRollTracker(DiceRollTracker* dt);

private:
    exprtk::symbol_table<long double> symbol_table;

    dice_roll<long double> roll;
    random_int<long double> rand_int;
    meemo_operation<long double> meemo;
    gcd<long double> GCD;
    lcm<long double> LCM;
    xrt<long double> xrt_op;
    factorial<long double> fact;

    QRegularExpression re{"\\b(?<number>\\d+)d(?<sides>\\d+)\\b"};

    // Supergolden Ratio
    constexpr long double f(long double x);
    constexpr long double f_prime(long double x);
    constexpr long double newtonRaphson(long double init, long double tol, int max_iters);
    constexpr long double constexpr_abs(long double x);
};

#endif // EXPRTKENGINE_H
