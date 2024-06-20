#include "dicedockwidget.h"
#include "ui_dicedockwidget.h"

#include <iostream>

DiceDockWidget::DiceDockWidget(DiceRollTracker *dt, QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::DiceDockWidget)
    , dt(dt)
{
    ui->setupUi(this);

    e.setDiceRollTracker(this->dt);

    connect(dt, &DiceRollTracker::changed, this, &DiceDockWidget::on_updated_dt);

    this->ui->d4->setPixmap(QPixmap(":/ui/dice/symbolic-dark/d4.svg"));
    this->ui->d4->setMinimumSize(QSize(32,32));
    this->ui->d4->setMaximumSize(QSize(32,32));
    this->ui->d4SpinBox->setMinimum(1);
    this->ui->d4SpinBox->setValue(1);
    //connect(this->ui->d4, &QClickableLabel::pressed, this, &DiceDockWidget::on_d4_clicked);

    this->ui->d6->setPixmap(QPixmap(":/ui/dice/symbolic-dark/d6.svg"));
    this->ui->d6->setMinimumSize(QSize(32,32));
    this->ui->d6->setMaximumSize(QSize(32,32));
    this->ui->d6SpinBox->setMinimum(1);
    this->ui->d6SpinBox->setValue(1);
    //connect(this->ui->d6, &QClickableLabel::clicked, this, &DiceDockWidget::on_d6_clicked);

    this->ui->d8->setPixmap(QPixmap(":/ui/dice/symbolic-dark/d8.svg"));
    this->ui->d8->setMinimumSize(QSize(32,32));
    this->ui->d8->setMaximumSize(QSize(32,32));
    this->ui->d8SpinBox->setMinimum(1);
    this->ui->d8SpinBox->setValue(1);
    //connect(this->ui->d8, &QClickableLabel::clicked, this, &DiceDockWidget::on_d8_clicked);

    this->ui->d10->setPixmap(QPixmap(":/ui/dice/symbolic-dark/d10.svg"));
    this->ui->d10->setMinimumSize(QSize(32,32));
    this->ui->d10->setMaximumSize(QSize(32,32));
    this->ui->d10SpinBox->setMinimum(1);
    this->ui->d10SpinBox->setValue(1);
    //connect(this->ui->d10, &QClickableLabel::clicked, this, &DiceDockWidget::on_d10_clicked);

    this->ui->d12->setPixmap(QPixmap(":/ui/dice/symbolic-dark/d12.svg"));
    this->ui->d12->setMinimumSize(QSize(32,32));
    this->ui->d12->setMaximumSize(QSize(32,32));
    this->ui->d12SpinBox->setMinimum(1);
    this->ui->d12SpinBox->setValue(1);
    //connect(this->ui->d12, &QClickableLabel::clicked, this, &DiceDockWidget::on_d12_clicked);

    this->ui->d20->setPixmap(QPixmap(":/ui/dice/symbolic-dark/d20.svg"));
    this->ui->d20->setMinimumSize(QSize(32,32));
    this->ui->d20->setMaximumSize(QSize(32,32));
    this->ui->d20SpinBox->setMinimum(1);
    this->ui->d20SpinBox->setValue(1);
    //connect(this->ui->d20, &QClickableLabel::clicked, this, &DiceDockWidget::on_d20_clicked);

    this->ui->dPercent->setPixmap(QPixmap(":/ui/dice/symbolic-dark/dPercent.svg"));
    this->ui->dPercent->setMinimumSize(QSize(32,32));
    this->ui->dPercent->setMaximumSize(QSize(32,32));
    this->ui->dPercentSpinBox->setMinimum(1);
    this->ui->dPercentSpinBox->setValue(1);
    //connect(this->ui->dPercent, &QClickableLabel::clicked, this, &DiceDockWidget::on_dPercent_clicked);
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

void DiceDockWidget::on_d4_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d4);
}

void DiceDockWidget::on_d6_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d6);
}

void DiceDockWidget::on_d8_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d8);
}

void DiceDockWidget::on_d10_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d10);
}

void DiceDockWidget::on_d12_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d12);
}

void DiceDockWidget::on_d20_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d20);
}

void DiceDockWidget::on_dPercent_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d100);
}

inline void DiceDockWidget::quickDiceRoll_Helper(DiceDockWidget::DDWDice d)
{
    const int sides = int(d);
    int num = -1;

    switch (d)
    {
    case DDWDice::d4:
        num = this->ui->d4SpinBox->value();
        break;
    case DDWDice::d6:
        num = this->ui->d6SpinBox->value();
        break;
    case DDWDice::d8:
        num = this->ui->d8SpinBox->value();
        break;
    case DDWDice::d10:
        num = this->ui->d10SpinBox->value();
        break;
    case DDWDice::d12:
        num = this->ui->d12SpinBox->value();
        break;
    case DDWDice::d20:
        num = this->ui->d20SpinBox->value();
        break;
    case DDWDice::d100:
        num = this->ui->dPercentSpinBox->value();
        break;
    }

    const QString currentText = this->ui->historyTextEdit->toPlainText();
    const QString dice = QString::number(num) + "d" + QString::number(sides);
    const QString fnFormat = "dice(" + QString::number(num) + "," + QString::number(sides) + ")";
    QString answer;

    try{
        answer = currentText + dice + ": " +QString::number(this->e.evaluate(fnFormat)) + "\n";
    }
    catch (const ExprTkParseException &e){
        answer = currentText + "Could not parse: \"" + fnFormat + "\"\n";
    }

    this->ui->historyTextEdit->setText(answer);
}

