#ifndef DOWNLOADSFAILEDDIALOGWIDGET_H
#define DOWNLOADSFAILEDDIALOGWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QVariant>
#include <QMap>
#include <QString>
#include <QEventLoop>

#include "fnggeneratepagehtmlparser.h"

namespace Ui {
class DownloadsFailedDialogWidget;
}

class DownloadsFailedDialogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadsFailedDialogWidget(QList<FNGGeneratorItem> items, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~DownloadsFailedDialogWidget();

    QList<QTreeWidgetItem *> getSelected();

signals:
    void dialogClosed();

private slots:
    void on_failList_itemSelectionChanged();

    void on_dnrButton_clicked();

    void on_rButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::DownloadsFailedDialogWidget *ui;

    QList<QTreeWidgetItem *> selected;
    QList<FNGGeneratorItem> items;
    QMap<QString, QTreeWidgetItem *> treeItems;
};

namespace DownloadMessageBox
{

    [[maybe_unused]] static QList<QTreeWidgetItem *> dlfailed(QList<FNGGeneratorItem> items, QWidget *parent = nullptr)
    {
        DownloadsFailedDialogWidget temp(items, parent, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        QEventLoop loop;
        QObject::connect(&temp, &DownloadsFailedDialogWidget::dialogClosed, &loop, &QEventLoop::quit);

        temp.show();
        loop.exec();

        QList<QTreeWidgetItem *> selected = temp.getSelected();

        temp.deleteLater();
        return selected;
    }

}

#endif // DOWNLOADSFAILEDDIALOGWIDGET_H
