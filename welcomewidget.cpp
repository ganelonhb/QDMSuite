#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QDMSWidget(parent)
    , ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    this->ui->diceImgLabel->setMinimumSize(QSize(64,64));
    this->ui->diceImgLabel->setMaximumSize(QSize(64,64));
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
