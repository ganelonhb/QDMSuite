#include "fantasynamegeneratorwidget.h"
#include "ui_fantasynamegeneratorwidget.h"

FantasyNameGeneratorWidget::FantasyNameGeneratorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FantasyNameGeneratorWidget)
{
    ui->setupUi(this);
}

FantasyNameGeneratorWidget::~FantasyNameGeneratorWidget()
{
    delete ui;
}
