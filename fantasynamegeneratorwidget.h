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

#include <cpptoml/cpptoml.h>

#include "qdmswidget.hpp"
#include "fantasynamegeneratordownloadwidget.h"
#include "fngitemmodel.h"

namespace Ui {
class FantasyNameGeneratorWidget;
}

struct FNG
{
    QString name;
    QString script;
    QString entryPoint;

    QMap<QString, QString> genders;
};

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

private:
    Ui::FantasyNameGeneratorWidget *ui;

    FantasyNameGeneratorDownloadWidget *dl;
    QTimer *timer;
    FNGItemModel *model;

    QButtonGroup *buttonGroup;

    QJSEngine *jse;

    FNG *fng;
};

#endif // FANTASYNAMEGENERATORWIDGET_H
