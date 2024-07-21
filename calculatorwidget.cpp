#include "calculatorwidget.h"
#include "ui_calculatorwidget.h"

CalculatorWidget::CalculatorWidget(DiceRollTracker *dt, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CalculatorWidget)
    , secondButtonClicked(false)
    , dt(dt)
{
    ui->setupUi(this);

    int fontId = QFontDatabase::addApplicationFont(":/ui/fonts/nihonium113/Nihonium113.ttf");

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont lcdFont = QFont(fontFamily);

    QFontInfo fontInfo(lcdFont);
    int pointSize = 16;

    if (fontInfo.pixelSize() > 0 && fontInfo.pointSize() == 0)
    {
        int dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();

        int pixelSize = static_cast<int>((pointSize * dpi) / 72);

        lcdFont.setPixelSize(pixelSize);
    }
    else
    {
        lcdFont.setPointSize(pointSize);
    }

    this->ui->displayLineEdit->setFont(lcdFont);

    // Set the Data of every button.
    // Zero
    this->ui->zeroButton->setProperty("first", "0");
    this->ui->zeroButton->setProperty("second", "rand(");
    // Dot
    this->ui->decimalPushButton->setProperty("first", ".");
    this->ui->decimalPushButton->setProperty("second", ",");
    // E
    this->ui->timesTenPushButton->setProperty("first", "*10^");
    // One
    this->ui->oneButton->setProperty("first", "1");
    // Two
    this->ui->twoButton->setProperty("first", "2");
    // Three
    this->ui->threeButton->setProperty("first", "3");
    // Four
    this->ui->fourButton->setProperty("first", "4");
    // Five
    this->ui->fiveButton->setProperty("first", "5");
    // Six
    this->ui->sixButton->setProperty("first", "6");
    // Seven
    this->ui->sevenButton->setProperty("first", "7");
    this->ui->sevenButton->setProperty("second", "PI");
    // Eight
    this->ui->eightButton->setProperty("first", "8");
    this->ui->eightButton->setProperty("second", "e");
    // Nine
    this->ui->nineButton->setProperty("first", "9");
    // ANS
    this->ui->ansPushButton->setProperty("first", "42");
    // Plus
    this->ui->plusButton->setProperty("first", "+");
    this->ui->plusButton->setProperty("second", "nPr(");
    // Minus
    this->ui->minusButton->setProperty("first", "-");
    this->ui->minusButton->setProperty("second", "nCr(");
    // Times
    this->ui->multButton->setProperty("first", "*");
    this->ui->multButton->setProperty("second", "GCD(");
    // Div
    this->ui->divButton->setProperty("first", "/");
    this->ui->divButton->setProperty("second", "LCM(");
    // e^x
    this->ui->eXButoon->setProperty("first", "e^");
    // x^2
    this->ui->squaredbutton->setProperty("first", "^2");
    // x^3
    this->ui->cubedButton->setProperty("first", "^2");
    // pow
    this->ui->powButton->setProperty("first", "^");
    // Space
    this->ui->spaceButton->setProperty("first", " ");
    // Fact
    this->ui->factButton->setProperty("first", "!");
    // Open parenthesis
    this->ui->leftParenthesisButton->setProperty("first", "(");
    // Close parenthesis
    this->ui->rightParenthesisButton->setProperty("first", ")");
    // Sqrt
    this->ui->sqrtButton->setProperty("first", "sqrt(");
    // Cbrt
    this->ui->cubedRootButton->setProperty("first", "cbrt(");
    // Log
    this->ui->logButton->setProperty("first", "log(");
    // Ln
    this->ui->lnButton->setProperty("first", "ln(");
    // LogX
    this->ui->logXButton->setProperty("first", "logx(");
    // Sin
    this->ui->sinButton->setProperty("first", "sin(");
    this->ui->sinButton->setProperty("second", "asin(");
    // Cos
    this->ui->cosButton->setProperty("first", "cos(");
    this->ui->cosButton->setProperty("second", "acos(");
    // Tan
    this->ui->tanButton->setProperty("first", "tan(");
    this->ui->tanButton->setProperty("second", "atan(");
    // Sinh
    this->ui->sinhButton->setProperty("first", "sinh(");
    this->ui->sinhButton->setProperty("second", "asinh(");
    // Cosh
    this->ui->coshButton->setProperty("first", "cosh(");
    this->ui->coshButton->setProperty("second", "acosh(");
    // Tanh
    this->ui->tanhButton->setProperty("first", "tanh(");
    this->ui->tanhButton->setProperty("second", "atanh(");

    QPalette palette = this->ui->displayLineEdit->palette();
    palette.setColor(QPalette::Text, Qt::white);
    this->ui->displayLineEdit->setPalette(palette);

    this->ui->constButton->addMenuAction("pi", new QAction("Pi (𝜋)", this->ui->constButton));
    // connect pi action to menu.
    this->ui->constButton->addMenuAction("tau", new QAction("Tau (𝜏)", this->ui->constButton));

    this->ui->constButton->addMenuAction("phi", new QAction("Golden Ratio (𝜙)", this->ui->constButton));

    this->ui->constButton->addMenuAction("silver_ratio", new QAction("Silver Ratio (𝛿ₛ)", this->ui->constButton));

    this->ui->constButton->addMenuAction("supergolden", new QAction("Supergolden Ratio (𝜓)", this->ui->constButton));

    this->ui->constButton->addMenuAction("eulers_number", new QAction("Euler's Number (𝑒)", this->ui->constButton));

    QColor c = QColor(0, 112, 168);

    this->ui->zeroButton->setSecondaries("RANDINT", c);
    this->ui->zeroButton->setSize(5);
    this->ui->zeroButton->setOffset(QPoint(3,9));
    this->ui->sevenButton->setSecondaries("𝜋", c);
    this->ui->eightButton->setSecondaries("𝑒", c);
    this->ui->decimalPushButton->setSecondaries(",", c);
    this->ui->decimalPushButton->setOffset(QPoint(4, 10));

    this->ui->plusButton->setSecondaries("nPr", c);
    this->ui->plusButton->setSize(5);
    this->ui->plusButton->setOffset(QPoint(3,9));
    this->ui->minusButton->setSecondaries("nCr", c);
    this->ui->minusButton->setSize(5);
    this->ui->minusButton->setOffset(QPoint(3,9));
    this->ui->divButton->setSecondaries("LCM", c);
    this->ui->divButton->setSize(5);
    this->ui->divButton->setOffset(QPoint(3,9));
    this->ui->multButton->setSecondaries("GCD", c);
    this->ui->multButton->setSize(5);
    this->ui->multButton->setOffset(QPoint(3,9));
    this->ui->percentButton->setSecondaries("MOD", c);
    this->ui->percentButton->setSize(5);
    this->ui->percentButton->setOffset(QPoint(3,9));

    this->ui->sinButton->setSecondaries("SIN⁻¹", c);
    this->ui->sinButton->setSize(5);
    this->ui->sinButton->setOffset(QPoint(3,9));
    this->ui->cosButton->setSecondaries("COS⁻¹", c);
    this->ui->cosButton->setSize(5);
    this->ui->cosButton->setOffset(QPoint(3,9));
    this->ui->tanButton->setSecondaries("TAN⁻¹", c);
    this->ui->tanButton->setSize(5);
    this->ui->tanButton->setOffset(QPoint(3,9));
    this->ui->sinhButton->setSecondaries("SINH⁻¹", c);
    this->ui->sinhButton->setSize(5);
    this->ui->sinhButton->setOffset(QPoint(3,9));
    this->ui->coshButton->setSecondaries("COSH⁻¹", c);
    this->ui->coshButton->setSize(5);
    this->ui->coshButton->setOffset(QPoint(3,9));
    this->ui->tanhButton->setSecondaries("TANH⁻¹", c);
    this->ui->tanhButton->setSize(5);
    this->ui->tanhButton->setOffset(QPoint(3,9));

    this->ui->sqrtButton->setSecondaries("1d4", c);
    this->ui->sqrtButton->setOffset(QPoint(2,2));
    this->ui->sqrtButton->setSvg(":/ui/dice/symbolic-dark/d4.svg");

    this->ui->cubedRootButton->setSecondaries("1d6", c);
    this->ui->cubedRootButton->setOffset(QPoint(2,2));
    this->ui->cubedRootButton->setSvg(":/ui/dice/symbolic-dark/d6.svg");

    this->ui->xThRootButton->setSecondaries("1d8", c);
    this->ui->xThRootButton->setOffset(QPoint(2,2));
    this->ui->xThRootButton->setSvg(":/ui/dice/symbolic-dark/d8.svg");

    this->ui->logButton->setSecondaries("1d10", c);
    this->ui->logButton->setOffset(QPoint(2,2));
    this->ui->logButton->setSvg(":/ui/dice/symbolic-dark/d10.svg");

    this->ui->lnButton->setSecondaries("1d12", c);
    this->ui->lnButton->setOffset(QPoint(2,2));
    this->ui->lnButton->setSvg(":/ui/dice/symbolic-dark/d12.svg");

    this->ui->logXButton->setSecondaries("1d20", c);
    this->ui->logXButton->setOffset(QPoint(2,2));
    this->ui->logXButton->setSvg(":/ui/dice/symbolic-dark/d20.svg");

    this->ui->spaceButton->setSecondaries("1d%", c);
    this->ui->spaceButton->setOffset(QPoint(2,2));
    this->ui->spaceButton->setSvg(":/ui/dice/symbolic-dark/dPercent.svg");

    connect(this->ui->regularButtons, &QButtonGroup::buttonClicked, this, &CalculatorWidget::regularButtonClicked);
}

CalculatorWidget::~CalculatorWidget()
{
    delete ui;
}

void CalculatorWidget::on_secondButton_clicked()
{
    if (!this->secondButtonClicked)
    {
        this->ui->secondIndicator->setText("⬤");
        this->secondButtonClicked = true;
    }
    else
    {
        this->ui->secondIndicator->setText("");
        this->secondButtonClicked = false;
    }
}

void CalculatorWidget::regularButtonClicked(QAbstractButton *b)
{
    QString currentText = this->ui->displayLineEdit->text();

    if (!secondButtonClicked)
    {
        this->ui->displayLineEdit->setText(currentText + b->property("first").toString());
        return;
    }

    QVariant property = b->property("second");

    if (property.isValid())
    {
        this->ui->displayLineEdit->setText(currentText + property.toString());
        this->ui->secondIndicator->setText("");
        this->secondButtonClicked = false;
    }
}


void CalculatorWidget::on_acButton_clicked()
{
    this->ui->displayLineEdit->clear();
}


void CalculatorWidget::on_delButton_clicked()
{
    QString oldString = this->ui->displayLineEdit->text();
    QString newString = oldString.mid(0, oldString.length() - 1);
    this->ui->displayLineEdit->setText(newString);
}


void CalculatorWidget::on_sqrtButton_clicked()
{

}

