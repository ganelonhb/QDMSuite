#ifndef TABPRESSEDEVENTFILTER_H
#define TABPRESSEDEVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>

#include "draggabletabwidget.h"

class TabPressedEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit TabPressedEventFilter(QObject *parent = nullptr);

signals:
    void tabClicked(DraggableTabWidget *tabWidget);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // TABPRESSEDEVENTFILTER_H
