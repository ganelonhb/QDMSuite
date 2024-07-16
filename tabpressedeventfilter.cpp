#include "tabpressedeventfilter.h"

TabPressedEventFilter::TabPressedEventFilter(QObject *parent)
    : QObject{parent}
{}

bool TabPressedEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::FocusIn)
    {
        QWidget *widget = qobject_cast<QWidget *>(obj);
        while(widget && !qobject_cast<DraggableTabWidget *>(widget))
            widget = widget->parentWidget();

        if (DraggableTabWidget * tabWidget = qobject_cast<DraggableTabWidget *>(widget); tabWidget) {
            emit tabClicked(tabWidget);

            if (event->type() == QEvent::FocusIn) return true;
        }
    }

    return QObject::eventFilter(obj, event);
}
