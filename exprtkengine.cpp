#include "exprtkengine.h"

ExprTkEngine::ExprTkEngine()
{
    symbol_table.add_function("dice", this->roll);
    symbol_table.add_function("rand", this->rand_int);
    symbol_table.add_function("meemo", this->meemo);
    symbol_table.add_function("GCD", this->GCD);
    symbol_table.add_function("LCM", this->LCM);
    symbol_table.add_function("xrt", this->xrt_op);
    symbol_table.add_function("fact", this->fact);
    symbol_table.add_function("gamma", this->fact);

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


    return exp.value();
}

void ExprTkEngine::setDiceRollTracker(DiceRollTracker* dt)
{
    this->roll.tracker = dt;
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
