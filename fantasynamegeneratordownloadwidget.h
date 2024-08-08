#ifndef FANTASYNAMEGENERATORDOWNLOADWIDGET_H
#define FANTASYNAMEGENERATORDOWNLOADWIDGET_H

#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTreeWidgetItem>
#include <QCloseEvent>
#include <QShowEvent>
#include <QIcon>
#include <QList>
#include <QVariant>
#include <QStandardPaths>
#include <QDir>

#include "downloadsfaileddialogwidget.h"
#include "fnggeneratepagehtmlparser.h"
#include "fantasynamegeneratorhtmlparser.h"

namespace Ui {
class FantasyNameGeneratorDownloadWidget;
}

class FantasyNameGeneratorDownloadWidget : public QWidget
{
    Q_OBJECT

public:
    using QTreeWidgetItemPtrList = QList<QTreeWidgetItem *>;

    explicit FantasyNameGeneratorDownloadWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~FantasyNameGeneratorDownloadWidget();

    void download();
    bool dlInProgress() const;

signals:
    void downloadComplete(bool success);

    void closeRequested();
    void shown();

    void blockClose();
    void unblockClose();

protected:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void finished(QNetworkReply *q);

    void on_cancelButton_clicked();
    void on_unCheckAll_checkStateChanged(const Qt::CheckState &state);

    void on_treeWidget_itemSelectionChanged();

    void on_checkAllCheckBox_checkStateChanged(const Qt::CheckState &state);

    void on_checkSelectedCheckBox_checkStateChanged(const Qt::CheckState &state);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_downloadSelectedButton_clicked();

    void on_downloadAllButton_clicked();

    void onCloseRequested();
    void onShow();

private:
    static inline void iterateTreeItems(QTreeWidgetItem *item, Qt::CheckState state = Qt::Unchecked);
    static inline void setAllCheckStates(QTreeWidget *widget, Qt::CheckState state = Qt::Unchecked);
    static inline void setAllChildCheckStates(QTreeWidgetItem *item, Qt::CheckState state = Qt::Unchecked);
    static inline bool allChecked(QTreeWidget *widget);
    static inline void iterateTreeCheck(QTreeWidgetItem *item, bool& allChecked);

    static inline QTreeWidgetItemPtrList items(QTreeWidget *widget, bool onlyChecked = false);
    static inline void addTreeWidgetItemsToList(QTreeWidgetItem *item, QTreeWidgetItemPtrList &list, bool onlyChecked = false);

    inline QList<FNGGeneratorItem> downloadItems(QTreeWidgetItemPtrList items);
    Ui::FantasyNameGeneratorDownloadWidget *ui;

    QNetworkAccessManager *nw;

    FantasyNameGeneratorHtmlParser *parseHtml;

    QList<QNetworkReply *> activeReplies;
};

#endif // FANTASYNAMEGENERATORDOWNLOADWIDGET_H
