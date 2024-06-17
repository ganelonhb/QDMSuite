#ifndef EXPRTKENGINE_H
#define EXPRTKENGINE_H

#include <exprtk/exprtk.hpp>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "dice_roll.h"

class ExprTkEngine
{
public:
    ExprTkEngine();

    int evaluate(const QString& expression);

    void setDiceRollTracker(DiceRollTracker* dt);

private:
    exprtk::symbol_table<double> symbol_table;

    dice_roll<double> roll;

};

#endif // EXPRTKENGINE_H
