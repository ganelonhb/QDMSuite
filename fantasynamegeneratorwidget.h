#ifndef FANTASYNAMEGENERATORWIDGET_H
#define FANTASYNAMEGENERATORWIDGET_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QFileSystemModel>
#include <QItemSelection>
#include <QMap>
#include <QFile>
#include <QMessageBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QJSEngine>
#include <QFont>
#include <QFontDatabase>
#include <QLineEdit>
#include <QTreeView>
#include <QCompleter>
#include <QDesktopServices>

#include <cpptoml/cpptoml.h>

#include "qdmswidget.hpp"
#include "fantasynamegeneratordownloadwidget.h"
#include "fngitemmodel.h"
#include "treesortfilterproxymodel.h"
#include "keypresseventfilter.h"
#include "swearchecker.h"

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

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_generateButton_clicked();

    void on_clearPushButton_clicked();

    void on_goToFolderButton_clicked();

private:
    Ui::FantasyNameGeneratorWidget *ui;

    FantasyNameGeneratorDownloadWidget *dl;
    QTimer *timer;
    FNGItemModel *model;
    TreeSortFilterProxyModel *proxyModel;

    QButtonGroup *buttonGroup;
    QButtonGroup *choicesButtonGroup;

    QJSEngine *jse;

    QModelIndexList *lastIndeces{nullptr};
};

#endif // FANTASYNAMEGENERATORWIDGET_H
