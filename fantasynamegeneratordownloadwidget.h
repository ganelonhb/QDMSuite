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
    void on_unCheckAll_checkStateChanged(const Qt::CheckState &state);

    void on_treeWidget_itemSelectionChanged();

    void on_checkAllCheckBox_checkStateChanged(const Qt::CheckState &state);

    void on_checkSelectedCheckBox_checkStateChanged(const Qt::CheckState &state);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    static inline void iterateTreeItems(QTreeWidgetItem* item, Qt::CheckState state = Qt::Unchecked);
    static inline void setAllCheckStates(QTreeWidget* widget, Qt::CheckState state = Qt::Unchecked);
    static inline bool allChecked(QTreeWidget* widget);
    static inline void iterateTreeCheck(QTreeWidgetItem* item, bool& allChecked);
    Ui::FantasyNameGeneratorDownloadWidget *ui;

    QNetworkAccessManager *nw;
    html::parser p;
    html::node_ptr node;
};

#endif // FANTASYNAMEGENERATORDOWNLOADWIDGET_H
