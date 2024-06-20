#include "dicedockwidget.h"
#include "ui_dicedockwidget.h"

DiceDockWidget::DiceDockWidget(DiceRollTracker *dt, QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DiceDockWidget)
    , dt(dt)
{
    ui->setupUi(this);

    e.setDiceRollTracker(this->dt);

    connect(dt, &DiceRollTracker::changed, this, &DiceDockWidget::on_updated_dt);
}

DiceDockWidget::~DiceDockWidget()
{
    delete ui;
}

void DiceDockWidget::on_updated_dt()
{
    this->ui->rollHistoryList->clear();

    for (const DiceRoll& d : *this->dt)
    {
        const QString dString = "1d" + QString::number(d.sides()) + ": " + QString::number(d.result());
        this->ui->rollHistoryList->addItem(dString);
    }
}


void DiceDockWidget::on_expressionLineEdit_returnPressed()
{
    this->on_enterPushButton_clicked();
}

void DiceDockWidget::on_clearRollHistory_clicked()
{
    this->ui->rollHistoryList->clear();
    this->dt->clear();
}


void DiceDockWidget::on_clearExpressions_clicked()
{
    this->ui->historyTextEdit->clear();
}


void DiceDockWidget::on_enterPushButton_clicked()
{
    const QString currentText = this->ui->historyTextEdit->toPlainText();
    const QString lineEditText = this->ui->expressionLineEdit->text();
    QString answer;

    try{
        answer = currentText + lineEditText + ": " +QString::number(this->e.evaluate(lineEditText.simplified())) + "\n";
    }
    catch (const ExprTkParseException &e){
        answer = currentText + "Could not parse: \"" + lineEditText + "\"\n";
    }

    this->ui->historyTextEdit->setText(answer);

    this->ui->expressionLineEdit->clear();
}

