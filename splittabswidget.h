#ifndef SPLITTABSWIDGET_H
#define SPLITTABSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <functional>

#include "reportemptytabwidget.h"
#include "welcomewidget.h"

class SplitTabsWidget : public QWidget
{
    Q_OBJECT
public:
    enum class TabSplitType
    {
        HORIZONTAL,
        VERTICAL,
    };

    explicit SplitTabsWidget(QWidget *parent = nullptr);

    void createNewTab(TabSplitType split = TabSplitType::HORIZONTAL);

private slots:
    void tabEmpty(QWidget *w);

private:
    int numWidgets{0};
    QWidget *selected{nullptr};
};

#endif // SPLITTABSWIDGET_H
