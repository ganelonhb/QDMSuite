#ifndef DICEDOCKWIDGET_H
#define DICEDOCKWIDGET_H

#include <QDockWidget>

#include "exprtkengine.h"
#include "dicerolltracker.h"
#include "exprtkparseexception.h"
#include "qclickablelabel.h"

namespace Ui {
class DiceDockWidget;
}

class DiceDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DiceDockWidget(DiceRollTracker* dt = nullptr, QWidget *parent = nullptr);
    ~DiceDockWidget();

public slots:
    void on_updated_dt();

private slots:
    void on_expressionLineEdit_returnPressed();

    void on_clearRollHistory_clicked();

    void on_clearExpressions_clicked();

    void on_enterPushButton_clicked();

    void on_d4_clicked();
    void on_d6_clicked();
    void on_d8_clicked();
    void on_d10_clicked();
    void on_d12_clicked();
    void on_d20_clicked();
    void on_dPercent_clicked();

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
    Ui::DiceDockWidget *ui;
    DiceRollTracker *dt;
    ExprTkEngine e;
};


#endif // DICEDOCKWIDGET_H
