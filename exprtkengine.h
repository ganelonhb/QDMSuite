#ifndef EXPRTKENGINE_H
#define EXPRTKENGINE_H

#include <exprtk/exprtk.hpp>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QException>
#include <QtTypes>

#include "dice_roll.h"
#include "exprtk_methods.h"
#include "exprtkparseexception.h"

class ExprTkEngine
{
public:
    ExprTkEngine();

    double evaluate(const QString& expression);

    void setDiceRollTracker(DiceRollTracker* dt);

private:
    exprtk::symbol_table<double> symbol_table;

    dice_roll<double> roll;
    random_int<double> rand_int;
    meemo_operation<double> meemo;

    QRegularExpression re{"\\b(?<number>\\d+)d(?<sides>\\d+)\\b"};
};

#endif // EXPRTKENGINE_H
