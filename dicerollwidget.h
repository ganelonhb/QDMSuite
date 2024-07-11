#ifndef DICEROLLWIDGET_H
#define DICEROLLWIDGET_H

#include <QWidget>

#include "exprtkengine.h"
#include "dicerolltracker.h"
#include "exprtkparseexception.h"
#include "qclickablelabel.h"

namespace Ui {
class DiceRollWidget;
}

class DiceRollWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiceRollWidget(DiceRollTracker* dt = nullptr, QWidget *parent = nullptr);
    ~DiceRollWidget();

public slots:
    void on_updated_dt();

private slots:
    void on_expressionsLineEdit_returnPressed();

    void on_clearRollsHistory_clicked();

    void on_clearExpressionsHistory_clicked();

    void on_expressionsEnter_clicked();

    void on_d4Icon_clicked();
    void on_d6Icon_clicked();
    void on_d8Icon_clicked();
    void on_d10Icon_clicked();
    void on_d12Icon_clicked();
    void on_d20Icon_clicked();
    void on_dPercentIcon_clicked();

private:
    enum DDWDice {
        d4 = 4,
        d6 = 6,
        d8 = 8,
        d10 = 10,
        d12 = 12,
        d20 = 20,
        d100 = 100,
    };

    inline void quickDiceRoll_Helper(DDWDice d);
    Ui::DiceRollWidget *ui;
    DiceRollTracker *dt;
    ExprTkEngine e;
};

#endif // DICEROLLWIDGET_H