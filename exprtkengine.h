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
    const long double ROUNDTHRESH = 1e-15;

    exprtk::symbol_table<long double> symbol_table;

    dice_roll<long double> m_roll;
    random_int<long double> m_rand;
    meemo_operation<long double> m_meemo;
    gcd<long double> m_GCD;
    lcm<long double> m_LCM;
    xrt<long double> m_xrt;
    factorial<long double> m_fact;
    exprtk_atan2<long double> m_atan2;
    ln<long double> m_ln;
    logb10<long double> m_log10;
    logx<long double> m_logx;

    QRegularExpression re{"\\b(?<number>\\d+)d(?<sides>\\d+)\\b"};

    // Supergolden Ratio
    constexpr long double f(long double x);
    constexpr long double f_prime(long double x);
    constexpr long double newtonRaphson(long double init, long double tol, int max_iters);
    constexpr long double constexpr_abs(long double x);
};

#endif // EXPRTKENGINE_H
