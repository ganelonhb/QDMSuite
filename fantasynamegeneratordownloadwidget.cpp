#include "fantasynamegeneratordownloadwidget.h"
#include "ui_fantasynamegeneratordownloadwidget.h"

FantasyNameGeneratorDownloadWidget::FantasyNameGeneratorDownloadWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , ui(new Ui::FantasyNameGeneratorDownloadWidget)
{
    ui->setupUi(this);

    this->ui->downloadWidget->setVisible(false);

    nw = new QNetworkAccessManager(this);

    connect(nw, &QNetworkAccessManager::finished, this, &FantasyNameGeneratorDownloadWidget::finished);

}

FantasyNameGeneratorDownloadWidget::~FantasyNameGeneratorDownloadWidget()
{
    delete ui;
}

void FantasyNameGeneratorDownloadWidget::download()
{
    nw->get(QNetworkRequest(QUrl("https://www.fantasynamegenerators.com/")));
}

void FantasyNameGeneratorDownloadWidget::finished(QNetworkReply *r)
{
    if (r->error() != QNetworkReply::NoError) {
        emit downloadComplete(false);
        r->deleteLater();
        return;
    }

    /* parse DOM and put in tree */
    r->deleteLater();

    emit downloadComplete(true);
}

void FantasyNameGeneratorDownloadWidget::on_cancelButton_clicked()
{
    this->close();
}

