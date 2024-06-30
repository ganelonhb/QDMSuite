#ifndef FANTASYNAMEGENERATORDOWNLOADWIDGET_H
#define FANTASYNAMEGENERATORDOWNLOADWIDGET_H

#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

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
};

#endif // FANTASYNAMEGENERATORDOWNLOADWIDGET_H
