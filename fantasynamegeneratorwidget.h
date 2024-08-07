#ifndef FANTASYNAMEGENERATORWIDGET_H
#define FANTASYNAMEGENERATORWIDGET_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QFileSystemModel>

#include "fngfilesystemmodel.h"
#include "fantasynamegeneratordownloadwidget.h"

namespace Ui {
class FantasyNameGeneratorWidget;
}

class FantasyNameGeneratorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FantasyNameGeneratorWidget(QWidget *parent = nullptr);
    ~FantasyNameGeneratorWidget();

    FantasyNameGeneratorDownloadWidget *fngDlWidget();

private slots:
    void on_downloadPushButton_clicked();
    void on_fngDone(bool success);
    void timer_timeout();

private:
    Ui::FantasyNameGeneratorWidget *ui;

    FantasyNameGeneratorDownloadWidget *dl;
    QTimer *timer;
    FNGFileSystemModel model;
};

#endif // FANTASYNAMEGENERATORWIDGET_H
