#ifndef DICEDOCKWIDGET_H
#define DICEDOCKWIDGET_H

#include <QDockWidget>

#include "exprtkengine.h"
#include "dicerolltracker.h"
#include "exprtkparseexception.h"

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

private:
    Ui::DiceDockWidget *ui;
    DiceRollTracker *dt;
    ExprTkEngine e;
};

#endif // DICEDOCKWIDGET_H
