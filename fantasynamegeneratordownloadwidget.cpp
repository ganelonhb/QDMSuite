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

    QList<QTreeWidgetItem *> items;
    for (size_t i = 1; i < selected.size() - 4; ++i)
    {
        QString name = QString::fromStdString(selected[i]->to_text()).split('\n')[0].simplified();

        QTreeWidgetItem *item = new QTreeWidgetItem(0);
        item->setText(0, name);

        if (name == "Fantasy & Folklore")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/fantasy-and-folklore.svg"));
        if (name == "Real Names")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/real-names.svg"));
        if (name == "Places & Locations")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/places-and-locations.svg"));
        if (name == "Other Names")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/other-names.svg"));

        items.append(item);
    }

    this->ui->treeWidget->insertTopLevelItems(0, items);

    /* parse DOM and put in tree */
    r->deleteLater();

    emit downloadComplete(true);
}

void FantasyNameGeneratorDownloadWidget::on_cancelButton_clicked()
{
    this->close();
}

