#include "dicerollwidget.h"
#include "ui_dicerollwidget.h"

DiceRollWidget::DiceRollWidget(DiceRollTracker *dt, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DiceRollWidget)
    , dt(dt)
{
    ui->setupUi(this);

    e.setDiceRollTracker(this->dt);

    connect(dt, &DiceRollTracker::changed, this, &DiceRollWidget::on_updated_dt);
}

DiceRollWidget::~DiceRollWidget()
{
    delete ui;
}

void DiceRollWidget::on_updated_dt()
{
    this->ui->rollsHistoryList->clear();

    for (const DiceRoll& d : *this->dt)
    {
        const QString dString = "1d" + QString::number(d.sides()) + ": " + QString::number(d.result());
        this->ui->rollsHistoryList->addItem(dString);
    }
}


void DiceRollWidget::on_expressionsLineEdit_returnPressed()
{
    this->on_expressionsEnter_clicked();
}

void DiceRollWidget::on_clearRollsHistory_clicked()
{
    this->ui->rollsHistoryList->clear();
    this->dt->clear();
}


void DiceRollWidget::on_clearExpressionsHistory_clicked()
{
    this->ui->expressionHistoryTextEdit->clear();
}


void DiceRollWidget::on_expressionsEnter_clicked()
{
    const QString currentText = this->ui->expressionHistoryTextEdit->toPlainText();
    const QString lineEditText = this->ui->expressionsLineEdit->text();

    QString answer;

    if (lineEditText.simplified().length())
    {
        try{
            answer = currentText + lineEditText + ": " + int128ToString(this->e.evaluate(lineEditText.simplified())) + "\n";
        }
        catch (const ExprTkParseException &e){
            answer = currentText + "Could not parse: \"" + lineEditText + "\"\n";
        }
    }
    else
    {
        answer = currentText + "You haven't written anything in the expression field.\n";
    }

    this->ui->expressionHistoryTextEdit->setText(answer);

    this->ui->expressionsLineEdit->clear();
}

void DiceRollWidget::on_d4Icon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d4);
}

void DiceRollWidget::on_d6Icon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d6);
}

void DiceRollWidget::on_d8Icon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d8);
}

void DiceRollWidget::on_d10Icon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d10);
}

void DiceRollWidget::on_d12Icon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d12);
}

void DiceRollWidget::on_d20Icon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d20);
}

void DiceRollWidget::on_dPercentIcon_clicked()
{
    this->quickDiceRoll_Helper(DDWDice::d100);
}

inline void DiceRollWidget::quickDiceRoll_Helper(DiceRollWidget::DDWDice d)
{
    const int sides = int(d);
    int num = -1;

    switch (d)
    {
    case DDWDice::d4:
        num = this->ui->d4Spin->value();
        break;
    case DDWDice::d6:
        num = this->ui->d6Spin->value();
        break;
    case DDWDice::d8:
        num = this->ui->d8Spin->value();
        break;
    case DDWDice::d10:
        num = this->ui->d10Spin->value();
        break;
    case DDWDice::d12:
        num = this->ui->d12Spin->value();
        break;
    case DDWDice::d20:
        num = this->ui->d20Spin->value();
        break;
    case DDWDice::d100:
        num = this->ui->dPercentSpin->value();
        break;
    }

    const QString currentText = this->ui->expressionHistoryTextEdit->toPlainText();
    const QString dice = QString::number(num) + "d" + QString::number(sides);
    const QString fnFormat = "dice(" + QString::number(num) + "," + QString::number(sides) + ")";
    QString answer;

    try{
        answer = currentText + dice + ": " + int128ToString(this->e.evaluate(fnFormat)) + "\n";
    }
    catch (const ExprTkParseException &e){
        answer = currentText + "Could not parse: \"" + fnFormat + "\"\n";
    }

    this->ui->expressionHistoryTextEdit->setText(answer);
}

inline QString DiceRollWidget::int128ToString(qint128 value)
{
    std::ostringstream oss;

    if (value < 0)
    {
        value = -value;
        oss << '-';
    }

    if (value == 0)
    {
        oss << '0';
        return QString::fromStdString(oss.str());
    }

    char c[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    std::string result;
    while(value != 0)
    {
        int ones = value % 10;
        result.push_back(c[ones]);
        value /= 10;
    }

    std::reverse(result.begin(), result.end());
    oss << result;

    return QString::fromStdString(oss.str());
}
