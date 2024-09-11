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

void AcknowledgementWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    QFile f(":/docs/Acknowledgements/" + currentText + ".md");

    ui->scrollArea->verticalScrollBar()->setValue(0);
    ui->scrollArea->horizontalScrollBar()->setValue(0);

    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
        return ui->docs->setText(f.readAll());

    ui->docs->setText("");
}


void AcknowledgementWindow::on_docs_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

