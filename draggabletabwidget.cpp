#include "draggabletabwidget.h"

DraggableTabWidget::DraggableTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    this->setAcceptDrops(true);

    DraggableTabBar *tabBar = new DraggableTabBar(this);

    setTabBar(tabBar);
    connect(tabBar, &DraggableTabBar::startDrag, this, &DraggableTabWidget::onStartDrag);


}

void DraggableTabWidget::onStartDrag(QWidget *w, const QPoint &pos, const QPixmap pix)
{
    Q_UNUSED(pos);

    int index = -1;

    for (int i = 0; i < count(); ++i)
    {
        if (widget(i) == w)
        {
            index = i;
            break;
        }
    }

    if (index == -1) return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/tab-widget", serializePtr(this->widget(index)));
    mimeData->setData("application/draggable-tab-widget", serializePtr(this));
    mimeData->setData("application/pid", QByteArray::number(QCoreApplication::applicationPid()));
    drag->setMimeData(mimeData);

    drag->setPixmap(pix);
    drag->setHotSpot(this->tabBar()->tabRect(index).topLeft());

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);

    Q_UNUSED(dropAction);
}

void DraggableTabWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (
        event->mimeData()->hasFormat("application/tab-widget")
        && event->mimeData()->hasFormat("application/draggable-tab-widget")
        && event->mimeData()->hasFormat("application/pid")
    ) {
        event->acceptProposedAction();
    }
}

void DraggableTabWidget::dropEvent(QDropEvent *event)
{
    if (
        event->mimeData()->hasFormat("application/tab-widget")
        && event->mimeData()->hasFormat("application/draggable-tab-widget")
        && event->mimeData()->hasFormat("application/pid")
    ) {
        int pid = event->mimeData()->data("application/pid").toInt();

        if (pid != QCoreApplication::applicationPid())
        {
            QMessageBox::information(this, "Drop Not Supported", "Dropping tabs between instances of Q.D.M.S. is not supported yet, but will be available in a future version.\nSorry for the inconvenience!");

            event->ignore();
            return;
        }

        QWidget *w = qobject_cast<QWidget *>(deserializePtr(event->mimeData()->data("application/tab-widget")));
        int fromIndex = -1;

        DraggableTabWidget *from = qobject_cast<DraggableTabWidget *>(deserializePtr(event->mimeData()->data("application/draggable-tab-widget")));
        for (int i = 0; i < from->count(); ++i)
        {
            if (from->widget(i) == w)
            {
                fromIndex = i;
                break;
            }
        }

        if (from == this || fromIndex == -1)
        {
            event->ignore();
            return;
        }

        QString tabText = from->tabBar()->tabText(fromIndex);
        QWidget *tabContent = from->widget(fromIndex);

        addTab(tabContent, tabText);
        setCurrentIndex(count() - 1);

        emit from->dropRemoveEvent();
        emit dropAccepted();

        event->acceptProposedAction();
    }
}

inline QByteArray DraggableTabWidget::serializePtr(QObject * obj)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    quintptr ptrValue = reinterpret_cast<quintptr>(obj);
    out << ptrValue;
    return byteArray;
}

inline QObject* DraggableTabWidget::deserializePtr(const QByteArray& byteArray)
{
    QDataStream in(byteArray);
    quintptr ptrValue;
    in >> ptrValue;
    return reinterpret_cast<QObject *>(ptrValue);
}
