#include "calculatorwidget.h"
#include "ui_calculatorwidget.h"

CalculatorWidget::CalculatorWidget(DiceRollTracker *dt, QWidget *parent)
    : QDMSWidget(parent)
    , ui(new Ui::CalculatorWidget)
    , secondButtonClicked(false)
    , dt(dt)
{
    ui->setupUi(this);

    int fontId = QFontDatabase::addApplicationFont(":/ui/fonts/Unifont/unifont-15.1.05.otf");
    this->e.setDiceRollTracker(dt);

    equalsPushed = false;

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
    this->ui->oneButton->setProperty("second", "γ");
    // Two
    this->ui->twoButton->setProperty("first", "2");
    // Three
    this->ui->threeButton->setProperty("first", "3");
    // Four
    this->ui->fourButton->setProperty("first", "4");
    this->ui->fourButton->setProperty("second", "φ");
    // Five
    this->ui->fiveButton->setProperty("first", "5");
    this->ui->fiveButton->setProperty("second", "δₛ");
    // Six
    this->ui->sixButton->setProperty("first", "6");
    this->ui->sixButton->setProperty("second", "ψ");
    // Seven
    this->ui->sevenButton->setProperty("first", "7");
    this->ui->sevenButton->setProperty("second", "π");
    // Eight
    this->ui->eightButton->setProperty("first", "8");
    this->ui->eightButton->setProperty("second", "ℯ");
    // Nine
    this->ui->nineButton->setProperty("first", "9");
    this->ui->nineButton->setProperty("second", "τ");
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
    this->ui->eXButoon->setProperty("first", "ℯ^");
    // x^2
    this->ui->squaredbutton->setProperty("first", "^2");
    // x^3
    this->ui->cubedButton->setProperty("first", "^3");
    // pow
    this->ui->powButton->setProperty("first", "^");
    // Space
    this->ui->spaceButton->setProperty("first", " ");
    this->ui->spaceButton->setProperty("second", "1d100");
    // Fact
    this->ui->factButton->setProperty("first", "fact(");
    // Open parenthesis
    this->ui->leftParenthesisButton->setProperty("first", "(");
    // Close parenthesis
    this->ui->rightParenthesisButton->setProperty("first", ")");
    // Sqrt
    this->ui->sqrtButton->setProperty("first", "sqrt(");
    this->ui->sqrtButton->setProperty("second", "1d4");
    // Cbrt
    this->ui->cubedRootButton->setProperty("first", "cbrt(");
    this->ui->cubedRootButton->setProperty("second", "1d6");
    // xrt
    this->ui->xThRootButton->setProperty("first", "xrt(");
    this->ui->xThRootButton->setProperty("second", "1d8");
    // Log
    this->ui->logButton->setProperty("first", "log10(");
    this->ui->logButton->setProperty("second", "1d10");
    // Ln
    this->ui->lnButton->setProperty("first", "ln(");
    this->ui->lnButton->setProperty("second", "1d12");
    // LogX
    this->ui->logXButton->setProperty("first", "logn(");
    this->ui->logXButton->setProperty("second", "1d20");
    // Sin
    this->ui->sinButton->setProperty("first", "sin(");
    this->ui->sinButton->setProperty("second", "csc(");
    // Cos
    this->ui->cosButton->setProperty("first", "cos(");
    this->ui->cosButton->setProperty("second", "sec(");
    // Tan
    this->ui->tanButton->setProperty("first", "tan(");
    this->ui->tanButton->setProperty("second", "cot(");
    // Sinh
    this->ui->sinhButton->setProperty("first", "sinh(");
    this->ui->sinhButton->setProperty("second", "asinh(");
    // Cosh
    this->ui->coshButton->setProperty("first", "cosh(");
    this->ui->coshButton->setProperty("second", "acosh(");
    // Tanh
    this->ui->tanhButton->setProperty("first", "tanh(");
    this->ui->tanhButton->setProperty("second", "atanh(");
    // Percent
    this->ui->percentButton->setProperty("first", "");
    this->ui->percentButton->setProperty("second", "%");

    // Const Menu
    QPalette palette = this->ui->displayLineEdit->palette();
    palette.setColor(QPalette::Text, Qt::white);
    this->ui->displayLineEdit->setPalette(palette);

    QAction *piAction = new QAction("Pi (π)", this->ui->constButton);
    piAction->setData("π");
    this->ui->constButton->addMenuAction("pi", piAction);

    QAction *eulerAction = new QAction("Euler's Number (e)", this->ui->constButton);
    eulerAction->setData("ℯ");
    this->ui->constButton->addMenuAction("eulers_number", eulerAction);

    QAction *tauAction = new QAction("Tau (τ)", this->ui->constButton);
    tauAction->setData("τ");
    this->ui->constButton->addMenuAction("tau", tauAction);

    QAction *grAction = new QAction("Golden Ratio (φ)", this->ui->constButton);
    grAction->setData("φ");
    this->ui->constButton->addMenuAction("phi", grAction);

    QAction *srAction = new QAction("Silver Ratio (δₛ)", this->ui->constButton);
    srAction->setData("δₛ");
    this->ui->constButton->addMenuAction("silver_ratio", srAction);

    QAction *sgrAction = new QAction("Supergolden Ratio (ψ)", this->ui->constButton);
    sgrAction->setData("ψ");
    this->ui->constButton->addMenuAction("supergolden", sgrAction);

    QAction *emAction = new QAction("Euler-Mascheroni (γ)", this->ui->constButton);
    emAction->setData("γ");
    this->ui->constButton->addMenuAction("euler_ma", emAction);

    connect(this->ui->constButton->getMenu(), &QMenu::triggered, this, &CalculatorWidget::constMenuActionTriggered);

    // Func menu
    QMenu *funcMenu = this->ui->funcButton->getMenu();

    // Basic
    QMenu *basic = new QMenu("Basic", funcMenu);

    QAction *basicMod = new QAction("mod(x)", basic);
    basicMod->setData("mod(");
    basic->addAction(basicMod);

    QAction *basicMul = new QAction("mul(x, y, ...)", basic);
    basicMul->setData("mul(");
    basic->addAction(basicMul);

    QAction *basicSum = new QAction("sum(x, y, ...)", basic);
    basicSum->setData("sum(");
    basic->addAction(basicSum);

    // Trig
    QMenu *trig = new QMenu("Trigonometry", funcMenu);

    QAction *cosAction = new QAction("cos(x)", trig);
    cosAction->setData("cos(");
    trig->addAction(cosAction);

    QAction *sinAction = new QAction("sin(x)", trig);
    sinAction->setData("sin(");
    trig->addAction(sinAction);

    QAction *tanAction = new QAction("tan(x)", trig);
    tanAction->setData("tan(");
    trig->addAction(tanAction);

    QAction *secAction = new QAction("sec(x)", trig);
    secAction->setData("sec(");
    trig->addAction(secAction);

    QAction *cscAction = new QAction("csc(x)", trig);
    cscAction->setData("csc(");
    trig->addAction(cscAction);

    QAction *cotAction = new QAction("cot(x)", trig);
    cotAction->setData("cot(");
    trig->addAction(cotAction);

    QAction *asinAction = new QAction("asin(x)", trig);
    asinAction->setData("asin(");
    trig->addAction(asinAction);

    QAction *acosAction = new QAction("acos(x)", trig);
    acosAction->setData("acos(");
    trig->addAction(acosAction);

    QAction *atanAction = new QAction("atan(x)", trig);
    atanAction->setData("atan(");
    trig->addAction(atanAction);

    QAction *atan2Action = new QAction("atan2(y, x)", trig);
    atan2Action->setData("atan2(");
    trig->addAction(atan2Action);

    QAction *degreesAction = new QAction("rad2deg(x radians)", trig);
    degreesAction->setData("rad2deg(");
    trig->addAction(degreesAction);

    QAction *radiansAction = new QAction("deg2rad(x°)", trig);
    radiansAction->setData("deg2rad(");
    trig->addAction(radiansAction);

    funcMenu->addMenu(trig);

    // Hyperbolic Trig
    QMenu *htrig = new QMenu("Hyperbolic Trig", funcMenu);

    QAction *coshAction = new QAction("cosh(x)", htrig);
    coshAction->setData("cosh(");
    htrig->addAction(coshAction);

    QAction *sinhAction = new QAction("sinh(x)", htrig);
    sinhAction->setData("sinh(");
    htrig->addAction(sinhAction);

    QAction *tanhAction = new QAction("tanh(x)", htrig);
    tanhAction->setData("tanh(");
    htrig->addAction(tanhAction);

    QAction *acoshAction = new QAction("acosh(x)", htrig);
    acoshAction->setData("acosh(");
    htrig->addAction(acoshAction);

    QAction *asinhAction = new QAction("asinh(x)", htrig);
    asinhAction->setData("asinh(");
    htrig->addAction(asinhAction);

    QAction *atanhAction = new QAction("atanh(x)", htrig);
    atanhAction->setData("atanh(");
    htrig->addAction(atanhAction);

    funcMenu->addMenu(htrig);

    // Exp and Log
    QMenu *expLog = new QMenu("Exponentiation and Logarithms", funcMenu);

    QAction *expAction = new QAction("exp(x)", expLog);
    expAction->setData("exp(");
    expLog->addAction(expAction);

    QAction *lnAction = new QAction("ln(x)", expLog);
    lnAction->setData("ln(");
    expLog->addAction(lnAction);

    QAction *logAction = new QAction("log10(x)", expLog);
    logAction->setData("log10(");
    expLog->addAction(logAction);

    QAction *logxAction = new QAction("logn(b, x)", expLog);
    logxAction->setData("logn(");
    expLog->addAction(logAction);

    QAction *sqrtAction = new QAction("sqrt(x)", expLog);
    sqrtAction->setData("sqrt(");
    expLog->addAction(sqrtAction);

    QAction *cbrtAction = new QAction("cbrt(x)", expLog);
    cbrtAction->setData("cbrt(");
    expLog->addAction(cbrtAction);

    QAction *rootAction = new QAction("xrt(b, x)", expLog);
    rootAction->setData("xrt(");
    expLog->addAction(rootAction);

    funcMenu->addMenu(expLog);

    // Statistics

    // Rounding

    QMenu *manips = new QMenu("Rounding", funcMenu);

    QAction *manipAbs = new QAction("abs(x)", manips);
    manipAbs->setData("abs(");
    manips->addAction(manipAbs);

    QAction *manipCiel = new QAction("ciel(x)", manips);
    manipCiel->setData("ciel(");
    manips->addAction(manipCiel);

    QAction *manipFloor = new QAction("floor(x)", manips);
    manipFloor->setData("floor(");
    manips->addAction(manipFloor);

    QAction *manipRound = new QAction("round(x)", manips);
    manipAbs->setData("round(");
    manips->addAction(manipRound);

    funcMenu->addMenu(manips);

    // Equalities & Inequalities

    QMenu *eq = new QMenu("Equalities & Inequalities", funcMenu);

    QAction *eqEq = new QAction("x == y", eq);
    eqEq->setData(" == ");
    eq->addAction(eqEq);

    QAction *eqNeq = new QAction("x != y", eq);
    eqNeq->setData(" != ");
    eq->addAction(eqNeq);

    QAction *eqLt = new QAction("x < y", eq);
    eqLt->setData(" < ");
    eq->addAction(eqLt);

    QAction *eqLtEq = new QAction("x <= y", eq);
    eqLtEq->setData(" <= ");
    eq->addAction(eqLtEq);

    QAction *eqGt = new QAction("x > y", eq);
    eqGt->setData("> ");
    eq->addAction(eqGt);

    QAction *eqGtEq = new QAction("x >= y", eq);
    eqGtEq->setData(" >= ");
    eq->addAction(eqGtEq);

    funcMenu->addMenu(eq);

    // Bitwise

    QMenu *bitwise = new QMenu("Bitwise", funcMenu);

    QAction *bitwiseAnd = new QAction("x and y", bitwise);
    bitwiseAnd->setData(" and ");
    bitwise->addAction(bitwiseAnd);

    QAction *bitwiseNand = new QAction("x nand y", bitwise);
    bitwiseNand->setData(" nand ");
    bitwise->addAction(bitwiseNand);

    QAction *bitwiseOr = new QAction("x or y", bitwise);
    bitwiseOr->setData(" or ");
    bitwise->addAction(bitwiseOr);

    QAction *bitwiseNor = new QAction("x nor y", bitwise);
    bitwiseNor->setData(" nor ");
    bitwise->addAction(bitwiseNor);

    QAction *bitwiseXor = new QAction("x xor y", bitwise);
    bitwiseXor->setData(" xor ");
    bitwise->addAction(bitwiseXor);

    QAction *bitwiseXnor = new QAction("x xnor y", bitwise);
    bitwiseXnor->setData(" xnor ");
    bitwise->addAction(bitwiseXnor);

    funcMenu->addMenu(bitwise);

    connect(funcMenu, &QMenu::triggered, this, &CalculatorWidget::constMenuActionTriggered);

    QColor c = QColor(0, 112, 168);

    this->ui->zeroButton->setSecondaries("RANDINT", c);
    this->ui->zeroButton->setSize(5);
    this->ui->zeroButton->setOffset(QPoint(3,9));
    this->ui->sevenButton->setSecondaries("π", c);
    this->ui->eightButton->setSecondaries("e", c);
    this->ui->nineButton->setSecondaries("τ", c);
    this->ui->fourButton->setSecondaries("φ", c);
    this->ui->fiveButton->setSecondaries("δₛ", c);
    this->ui->sixButton->setSecondaries("ψ", c);
    this->ui->oneButton->setSecondaries("γ", c);
    //this->ui->
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

    this->ui->sinButton->setSecondaries("CSC", c);
    this->ui->sinButton->setSize(5);
    this->ui->sinButton->setOffset(QPoint(3,9));
    this->ui->cosButton->setSecondaries("SEC", c);
    this->ui->cosButton->setSize(5);
    this->ui->cosButton->setOffset(QPoint(3,9));
    this->ui->tanButton->setSecondaries("COT", c);
    this->ui->tanButton->setSize(5);
    this->ui->tanButton->setOffset(QPoint(3,9));
    this->ui->sinhButton->setSecondaries("ASINH", c);
    this->ui->sinhButton->setSize(5);
    this->ui->sinhButton->setOffset(QPoint(3,9));
    this->ui->coshButton->setSecondaries("SCOSH", c);
    this->ui->coshButton->setSize(5);
    this->ui->coshButton->setOffset(QPoint(3,9));
    this->ui->tanhButton->setSecondaries("ATANH", c);
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

    this->ui->ansPushButton->setSecondaries("PREV", c);
    this->ui->ansPushButton->setSize(5);
    this->ui->ansPushButton->setOffset(QPoint(3,9));

    connect(this->ui->regularButtons, &QButtonGroup::buttonClicked, this, &CalculatorWidget::regularButtonClicked);

    KeyPressEventFilter *enterPressed = new KeyPressEventFilter({Qt::Key_Return, Qt::Key_Enter}, this);
    this->installEventFilter(enterPressed);

    connect(enterPressed, &KeyPressEventFilter::triggered, this, &CalculatorWidget::on_equalsPushButton_clicked);
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

// TODO: Modify this button's behavior so that operators do not clear the display when equals was pushed.
void CalculatorWidget::regularButtonClicked(QAbstractButton *b)
{
    if (equalsPushed)
    {
        this->ui->displayLineEdit->clear();
        equalsPushed = false;
    }

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
    equalsPushed = false;
}


void CalculatorWidget::on_delButton_clicked()
{
    QString oldString = this->ui->displayLineEdit->text();
    QString newString = oldString.mid(0, oldString.length() - 1);
    this->ui->displayLineEdit->setText(newString);
    equalsPushed = false;
}

void CalculatorWidget::on_equalsPushButton_clicked()
{
    if (history.length() > 99)
        history.removeFirst();
    QString l = this->ui->displayLineEdit->text();
    history.append(l);

    const QString lineEditText =    l.replace("π", "(PI)")
                                     .replace("τ", "(TAU)")
                                     .replace("ℯ", "(EULER)")
                                     .replace("φ", "(GOLDEN)")
                                     .replace("δₛ", "(SILVER)")
                                     .replace("ψ", "(SUPERGOLD)")
                                     .replace("γ", "(E_M)");

    QString answer;

    if (lineEditText.simplified().length())
    {
        try{
            answer = doubleToQString(this->e.evaluate(lineEditText.simplified()));
        }
        catch (const ExprTkParseException &e){
            answer = "Err: Parse";
        }
        catch (const ExprTkDivByZeroException &e)
        {
            answer = "Err: Div by Zero";
        }
        catch (const ExprTkImaginaryException &e)
        {
            answer = "Err: Imaginary";
        }
        catch (const ExprTkOverflowException &e)
        {
            answer = "Err: Overflow";
        }
    }
    else
    {
        answer = "42";
    }

    this->ui->displayLineEdit->setText(answer);
    this->ui->ansPushButton->setProperty("first", answer);

    if (secondButtonClicked)
    {
        this->ui->secondIndicator->setText("");
        secondButtonClicked = false;
    }

    equalsPushed = true;
}

void CalculatorWidget::constMenuActionTriggered(QAction *action)
{
    QString currentText = this->ui->displayLineEdit->text();
    QString actionData = action->data().toString();

    this->ui->displayLineEdit->setText(currentText + actionData);
    this->ui->secondIndicator->setText("");
    this->secondButtonClicked = false;
}


void CalculatorWidget::on_ansPushButton_clicked()
{
    if (equalsPushed)
    {
        this->ui->displayLineEdit->clear();
        equalsPushed = false;
    }

    if (!secondButtonClicked)
    {
        QString currentText = this->ui->displayLineEdit->text();

        this->ui->displayLineEdit->setText(currentText + this->ui->ansPushButton->property("first").toString());
        return;
    }

    if (history.isEmpty())
        return this->ui->displayLineEdit->setText("42");

    this->ui->displayLineEdit->setText(history.last());
}

void CalculatorWidget::on_statsButton_clicked()
{
    QMessageBox::information(this->parentWidget(), "Not Yet Implemented", "User-defined functions are coming soon!");
}

