#include "acknowledgementwindow.h"
#include "ui_acknowledgementwindow.h"

AcknowledgementWindow::AcknowledgementWindow(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , ui(new Ui::AcknowledgementWindow)
{
    ui->setupUi(this);
}

AcknowledgementWindow::~AcknowledgementWindow()
{
    delete ui;
}
