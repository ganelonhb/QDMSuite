#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>
#include <QFont>
#include <QFontDatabase>
#include <QScreen>
#include <QAbstractButton>
#include <QFontInfo>

#include "dicerolltracker.h"
#include "exprtkengine.h"
#include "helper_functions.hpp"

namespace Ui {
class CalculatorWidget;
}

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorWidget(DiceRollTracker *dt = nullptr, QWidget *parent = nullptr);
    ~CalculatorWidget();

private slots:
    void on_secondButton_clicked();
    void regularButtonClicked(QAbstractButton *b);

    void on_acButton_clicked();

    void on_delButton_clicked();

    void on_equalsPushButton_clicked();

    void constMenuActionTriggered(QAction *action);

private:
    Ui::CalculatorWidget *ui;

    bool secondButtonClicked;
    ExprTkEngine e;

    DiceRollTracker *dt;
};

#endif // CALCULATORWIDGET_H
