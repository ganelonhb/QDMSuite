#include "exprtkengine.h"

#include <iostream>

ExprTkEngine::ExprTkEngine()
{
    symbol_table.add_function("dice", this->roll);
    symbol_table.add_constants();
}

int ExprTkEngine::evaluate(const QString& expression)
{
    exprtk::expression<double> exp;
    exprtk::parser<double> parser;

    exp.register_symbol_table(this->symbol_table);

    QString e = expression;

    QStringList result = e.split(' ');

    QRegularExpression re("(?<number>\\d+)d(?<sides>\\d+)");

    for (QString& str : result)
    {

        std::cout << str.toStdString() << ", ";
        if (QRegularExpressionMatch match = re.match(str); match.hasMatch()) {
            str.replace(
                match.captured(),
                "dice(" + match.captured("number") + "," + match.captured("sides") + ")"
            );
        }

        std::cout << str.toStdString() << "\n\n";
    }

    parser.compile(result.join(' ').toStdString(), exp);

    return exp.value();
}

void ExprTkEngine::setDiceRollTracker(DiceRollTracker* dt)
{
    this->roll.tracker = dt;
}
