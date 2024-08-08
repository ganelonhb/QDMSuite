#ifndef FANTASYNAMEGENERATORWIDGET_H
#define FANTASYNAMEGENERATORWIDGET_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QFileSystemModel>

#include "qdmswidget.hpp"
#include "fantasynamegeneratordownloadwidget.h"
#include "fngitemmodel.h"

namespace Ui {
class FantasyNameGeneratorWidget;
}

class FantasyNameGeneratorWidget : public QDMSWidget
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

    void onDlBlockClose();
    void onDlUnblockClose();

private:
    Ui::FantasyNameGeneratorWidget *ui;

    FantasyNameGeneratorDownloadWidget *dl;
    QTimer *timer;
    FNGItemModel *model;
};

#endif // FANTASYNAMEGENERATORWIDGET_H
