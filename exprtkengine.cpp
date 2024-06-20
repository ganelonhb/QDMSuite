#include "exprtkengine.h"

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
