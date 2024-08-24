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

template <std::floating_point number_t>
class ExprTkEngine
{
public:
    ExprTkEngine()
    {
        symbol_table.add_function("dice", this->m_roll);
        symbol_table.add_function("rand", this->m_rand);
        symbol_table.add_function("meemo", this->m_meemo);
        symbol_table.add_function("GCD", this->m_GCD);
        symbol_table.add_function("LCM", this->m_LCM);
        symbol_table.add_function("xrt", this->m_xrt);
        symbol_table.add_function("fact", this->m_fact);
        symbol_table.add_function("gamma", this->m_fact);
        symbol_table.add_function("atan2", this->m_atan2);
        symbol_table.add_function("ln", this->m_ln);
        symbol_table.add_function("log", this->m_log10);
        symbol_table.add_function("logx", this->m_logx);

        symbol_table.add_constant("EULER", std::numbers::e_v<number_t>);
        symbol_table.add_constant("GOLDEN", std::numbers::phi_v<number_t>);
        symbol_table.add_constant("E_M", std::numbers::egamma_v<number_t>);

        if constexpr(std::is_same_v<number_t, long double>)
        {
            constexpr long double TAUl = 2.L * 3.141592653589793238L;
            symbol_table.add_constant("TAU", TAUl);

            symbol_table.add_constant("SILVER", 1.L + std::sqrtl(2.L));
            symbol_table.add_constant("SUPERGOLD", newtonRaphson(1.5L, 1e-18L, 100));
        }
        else if constexpr(std::is_same_v<number_t, double>)
        {
            constexpr double TAU = 2. *  3.14159265358979323846;
            symbol_table.add_constant("TAU", TAU);

            symbol_table.add_constant("SILVER", 1. + std::sqrt(2.));
            symbol_table.add_constant("SUPERGOLD", newtonRaphson(1.5, 1e-12, 100));
        }
        else
        {
            constexpr float TAUf = 2.f * 3.1415927f;
            symbol_table.add_constant("TAU", TAUf);

            symbol_table.add_constant("SILVER", 1.f + std::sqrtf(2.f));
            symbol_table.add_constant("SUPERGOLD", newtonRaphson(1.5f, 1e-6f, 100));
        }

        symbol_table.add_constants();
    }

    number_t evaluate(const QString& expression)
    {
        exprtk::expression<number_t> exp;
        exprtk::parser<number_t> parser;

        exp.register_symbol_table(this->symbol_table);

        QString e = expression;

        QStringList result = e.split(' ');

        for (QString& str : result)
        {
            QRegularExpressionMatchIterator it = re.globalMatch(str);
            while (it.hasNext()) {
                QRegularExpressionMatch match = it.next();
                str.replace(
                    match.captured(),
                    "dice(" + match.captured("number") + "," + match.captured("sides") + ")"
                    );
            }
        }

        if (!parser.compile(result.join(' ').toStdString(), exp))
            throw ExprTkParseException();

        number_t value = exp.value();

        if constexpr(std::is_same_v<number_t, long double>)
        {
            number_t roundedValue = std::roundl(value);
            constexpr number_t roundThresh = 1e-18L;

            return std::fabsl(value - roundedValue) < roundThresh ? roundedValue : value;
        }
        else if constexpr(std::is_same_v<number_t, double>)
        {
            number_t roundedValue = std::round(value);
            constexpr number_t roundThresh = 1e-12;

            return std::fabs(value - roundedValue) < roundThresh ? roundedValue : value;
        }
        else if constexpr(std::is_same_v<number_t, float>)
        {
            number_t roundedValue = std::roundf(value);
            constexpr number_t roundThresh = 1e-6L;

            return std::fabsf(value - roundedValue) < roundThresh ? roundedValue : value;
        }
    }

    void setDiceRollTracker(DiceRollTracker* dt)
    {
        m_roll.tracker = dt;
    }

private:
    exprtk::symbol_table<number_t> symbol_table;

    dice_roll<number_t> m_roll;
    random_int<number_t> m_rand;
    meemo_operation<number_t> m_meemo;
    gcd<number_t> m_GCD;
    lcm<number_t> m_LCM;
    xrt<number_t> m_xrt;
    factorial<number_t> m_fact;
    exprtk_atan2<number_t> m_atan2;
    ln<number_t> m_ln;
    logb10<number_t> m_log10;
    logx<number_t> m_logx;

    QRegularExpression re{"\\b(?<number>\\d+)d(?<sides>\\d+)\\b"};

    // Supergolden Ratio
    constexpr number_t f(number_t x)
    {
        if constexpr(std::is_same_v<number_t, long double>)
            return std::powl(x, 3.L) - std::powl(x, 2.L) - 1.L;
        if constexpr(std::is_same_v<number_t, double>)
            return std::pow(x, 3.) - std::pow(x, 2.) - 1.;
        else
            return std::powf(x, 3.f) - std::powf(x, 2.f) - 1.f;
    }

    constexpr number_t f_prime(number_t x)
    {
        if constexpr(std::is_same_v<number_t, long double>)
            return 3.L * std::powl(x, 2.L) - 2.L * x;
        if constexpr(std::is_same_v<number_t, double>)
            return 3. * std::pow(x, 2.) - 2. * x;
        else
            return 3.f * std::powf(x, 2.f) - 2.f * x;
    }

    constexpr number_t newtonRaphson(number_t init, number_t tol, int max_iters)
    {
        number_t x = init;
        for (int i = 0; i < max_iters; ++i)
        {
            number_t fx = f(x);
            number_t fpx = f_prime(x);
            number_t x_new = x - fx / fpx;
            if (constexpr_abs(x_new - x) < tol)
            {
                return x_new;
            }

            x = x_new;
        }

        return x;
    }

    constexpr number_t constexpr_abs(number_t x)
    {
        if constexpr(std::is_same_v<number_t, long double>)
            return x < 0.L ? -x : x;
        else if constexpr(std::is_same_v<number_t, double>)
            return x < 0. ? -x : x;
        else
            return x < 0.f ? -x : x;
    }
};

#endif // EXPRTKENGINE_H
