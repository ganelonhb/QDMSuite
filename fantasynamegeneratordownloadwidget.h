#ifndef FANTASYNAMEGENERATORDOWNLOADWIDGET_H
#define FANTASYNAMEGENERATORDOWNLOADWIDGET_H

#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <htmlparser/html.hpp>
#include <QTreeWidgetItem>
#include <QIcon>
#include <QList>

#include <vector>

namespace Ui {
class FantasyNameGeneratorDownloadWidget;
}

class FantasyNameGeneratorDownloadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FantasyNameGeneratorDownloadWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~FantasyNameGeneratorDownloadWidget();

    void download();

signals:
    void downloadComplete(bool success);

private slots:
    void finished(QNetworkReply *q);

    void on_cancelButton_clicked();

private:
    Ui::FantasyNameGeneratorDownloadWidget *ui;

    QNetworkAccessManager *nw;
    html::parser p;
    html::node_ptr node;
};

#endif // FANTASYNAMEGENERATORDOWNLOADWIDGET_H
