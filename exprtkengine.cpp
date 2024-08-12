#include "exprtkengine.h"

ExprTkEngine::ExprTkEngine()
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

    symbol_table.add_constant("EULER", std::numbers::e);
    symbol_table.add_constant("TAU", 6.283185307179586);
    symbol_table.add_constant("GOLDEN", std::numbers::phi);
    symbol_table.add_constant("E_M", std::numbers::egamma);
    symbol_table.add_constant("SILVER", 1 + sqrt(2));
    symbol_table.add_constant("SUPERGOLD", newtonRaphson(1.5, 1e-12, 100));
    symbol_table.add_constants();
}

long double ExprTkEngine::evaluate(const QString& expression)
{
    exprtk::expression<long double> exp;
    exprtk::parser<long double> parser;

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

    long double value = exp.value();
    long double roundedValue = std::round(value);

    return std::fabsl(value - roundedValue) < ROUNDTHRESH ? roundedValue : value;
}

void ExprTkEngine::setDiceRollTracker(DiceRollTracker* dt)
{
    this->m_roll.tracker = dt;
}

constexpr long double ExprTkEngine::f(long double x)
{
    return pow(x, 3) - pow(x, 2) - 1.0;
}

constexpr long double ExprTkEngine::f_prime(long double x)
{
    return 3 * pow(x, 2) - 2 * x;
}

constexpr long double ExprTkEngine::newtonRaphson(long double init, long double tol, int max_iters)
{
    long double x = init;
    for (int i = 0; i < max_iters; ++i)
    {
        long double fx = f(x);
        long double fpx = f_prime(x);
        long double x_new = x - fx / fpx;
        if (constexpr_abs(x_new - x) < tol)
        {
            return x_new;
        }

        x = x_new;
    }

    return x;
}

constexpr long double ExprTkEngine::constexpr_abs(long double x)
{
    return x < 0 ? -x : x;
}
