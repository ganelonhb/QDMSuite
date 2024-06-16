#ifndef EXPRTKENGINE_H
#define EXPRTKENGINE_H

#include <exprtk/exprtk.hpp>
#include <QString>
#include <QStringTokenizer>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "dice_roll.h"

class ExprTkEngine
{
public:
    ExprTkEngine();

    int evaluate(const QString& expression);

private:
    exprtk::symbol_table<double> symbol_table;

    dice_roll<double> roll;

};

#endif // EXPRTKENGINE_H
