#ifndef SPLITTABSWIDGET_H
#define SPLITTABSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLayoutItem>
#include <QWidgetItem>
#include <QFrame>
#include <QPalette>
#include <QColor>
#include <QMessageBox>

#include "welcomewidget.h"
#include "draggabletabwidget.h"
#include "tabpressedeventfilter.h"
#include "fantasynamegeneratorwidget.h"

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
    DraggableTabWidget *selected();

public slots:
    void createHorizontalTab();
    void createVerticalTab();
    void onTabClicked(DraggableTabWidget *tab);

signals:
    void single();

private:
    DraggableTabWidget *_selected{nullptr};
    TabSplitMode mode{TabSplitMode::SINGLE};
    TabPressedEventFilter *tabPressedEventFilter;

    static inline void installEventFilterRecursively(QWidget *widget, QObject *filter);
};

#endif // SPLITTABSWIDGET_H
