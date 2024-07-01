#include "fantasynamegeneratordownloadwidget.h"
#include "ui_fantasynamegeneratordownloadwidget.h"

#include <iostream>

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

    node = p.parse(r->readAll().toStdString());

    std::vector<html::node *> selected = node->select("ul.navmenu>li");

    for (size_t i = 1; i < selected.size() - 2; ++i)
    {
        QString name = QString::fromStdString(selected[i]->to_text()).split('\n')[0];

        std::vector<html::node *> main = selected[i]->select("ol.mainOl>li");
        for (auto e : main)
        {
            if (e->get_attr("class") == "subList")
            {
                QString subListName = QString::fromStdString(e->to_text()).split('\n')[0];
                std::cout << subListName.toStdString() << "\n\n";
            }
        }
    }

    /* parse DOM and put in tree */
    r->deleteLater();

    emit downloadComplete(true);
}

void FantasyNameGeneratorDownloadWidget::on_cancelButton_clicked()
{
    this->close();
}

