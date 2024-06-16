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

    QRegularExpression re("\\d+d\\d+");

    parser.compile(e.toStdString(), exp);

    return exp.value();
}
