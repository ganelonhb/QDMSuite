#ifndef DOWNLOADSFAILEDDIALOGWIDGET_H
#define DOWNLOADSFAILEDDIALOGWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QVariant>
#include <QMap>
#include <QString>

#include "fnggeneratepagehtmlparser.h"

namespace Ui {
class DownloadsFailedDialogWidget;
}

class DownloadsFailedDialogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadsFailedDialogWidget(QList<FNGGeneratorItem> items, QWidget *parent = nullptr);
    ~DownloadsFailedDialogWidget();

private slots:
    void on_failList_itemSelectionChanged();

private:
    Ui::DownloadsFailedDialogWidget *ui;

    QList<FNGGeneratorItem> items;
    QMap<QString, QTreeWidgetItem *> treeItems;
};

#endif // DOWNLOADSFAILEDDIALOGWIDGET_H
