#ifndef SPLITTABSWIDGET_H
#define SPLITTABSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLayoutItem>
#include <QWidgetItem>
#include <QTabWidget>

#include <functional>

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
    enum class TabSplitMode
    {
        SINGLE,
        HORIZONTAL,
        VERTICAL,
    };

    explicit SplitTabsWidget(QWidget *parent = nullptr);

    void createNewTab(TabSplitType split = TabSplitType::HORIZONTAL);
    QTabWidget *selected();

public slots:
    void createHorizontalTab();
    void createVerticalTab();

signals:
    void single();

private:
    QTabWidget *_selected{nullptr};
    TabSplitMode mode{TabSplitMode::SINGLE};

};

#endif // SPLITTABSWIDGET_H
