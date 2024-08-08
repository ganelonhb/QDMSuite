#include "dicerollwidget.h"
#include "ui_dicerollwidget.h"

DiceRollWidget::DiceRollWidget(DiceRollTracker *dt, QWidget *parent)
    : QDMSWidget(parent)
    , ui(new Ui::DiceRollWidget)
    , dt(dt)
{
    ui->setupUi(this);

    e.setDiceRollTracker(this->dt);

    int fontId = QFontDatabase::addApplicationFont(":/ui/fonts/vinque/vinque rg.otf");
    this->e.setDiceRollTracker(dt);

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont fantasieFont = QFont(fontFamily);

    QFontInfo fontInfo(fantasieFont);
    int pointSize = 32;

    if (fontInfo.pixelSize() > 0 && fontInfo.pointSize() == 0)
    {
        int dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();

        int pixelSize = static_cast<int>((pointSize * dpi) / 72);

        fantasieFont.setPixelSize(pixelSize);
    }
    else
    {
        fantasieFont.setPointSize(pointSize);
    }

    this->ui->resultLabel->setFont(fantasieFont);

    pointSize = 14;

    if (fontInfo.pixelSize() > 0 && fontInfo.pointSize() == 0)
    {
        int dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();

        int pixelSize = static_cast<int>((pointSize * dpi) / 72);

        fantasieFont.setPixelSize(pixelSize);
    }
    else
    {
        fantasieFont.setPointSize(pointSize);
    }

    this->ui->diceLabel->setFont(fantasieFont);

    connect(dt, &DiceRollTracker::changed, this, &DiceRollWidget::on_updated_dt);

    constexpr QColor diceColor(255,255,255, 255 / 5);
    ui->d4Icon->setAnimationColor(diceColor);
    ui->d6Icon->setAnimationColor(diceColor);
    ui->d8Icon->setAnimationColor(diceColor);
    ui->d10Icon->setAnimationColor(diceColor);
    ui->d12Icon->setAnimationColor(diceColor);
    ui->d20Icon->setAnimationColor(diceColor);
    ui->dPercentIcon->setAnimationColor(diceColor);
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
            const QString result = doubleToQString(this->e.evaluate(lineEditText.simplified()));
            answer = currentText + lineEditText + ": " + result + "\n";

            this->ui->diceLabel->setText(lineEditText.simplified());
            this->ui->resultLabel->setText(result.simplified());
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
        const QString result = doubleToQString(this->e.evaluate(fnFormat));
        answer = currentText + dice + ": " + result + "\n";

        this->ui->resultLabel->setText(result.simplified());
        this->ui->diceLabel->setText(QString::number(num) + "d" + QString::number(sides));
    }
    catch (const ExprTkParseException &e){
        answer = currentText + "Could not parse: \"" + fnFormat + "\"\n";
    }

    this->ui->expressionHistoryTextEdit->setText(answer);
}

void DiceRollWidget::on_d4Spin_valueChanged(int sides)
{
    ui->d4Icon->setToolTip("Roll " + QString::number(sides) + "d4");
}


void DiceRollWidget::on_d6Spin_valueChanged(int sides)
{
    ui->d6Icon->setToolTip("Roll " + QString::number(sides) + "d6");
}


void DiceRollWidget::on_d8Spin_valueChanged(int sides)
{
    ui->d8Icon->setToolTip("Roll " + QString::number(sides) + "d8");
}


void DiceRollWidget::on_d10Spin_valueChanged(int sides)
{
    ui->d10Icon->setToolTip("Roll " + QString::number(sides) + "d10");
}


void DiceRollWidget::on_d12Spin_valueChanged(int sides)
{
    ui->d12Icon->setToolTip("Roll " + QString::number(sides) + "d12");
}


void DiceRollWidget::on_d20Spin_valueChanged(int sides)
{
    ui->d20Icon->setToolTip("Roll " + QString::number(sides) + "d20");
}


void DiceRollWidget::on_dPercentSpin_valueChanged(int sides)
{
    ui->dPercentIcon->setToolTip("Roll " + QString::number(sides) + "d100");
}

