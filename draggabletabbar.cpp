#include "draggabletabbar.h"

DraggableTabBar::DraggableTabBar(QWidget *parent)
    : QTabBar(parent)
    , dragging(false)
    , draggedTabIndex(-1)
{
    setElideMode(Qt::ElideRight);
    setExpanding(false);

    QPalette palette = QApplication::palette();

    QString normalBg = palette.color(QPalette::Mid).name(QColor::HexArgb);
    QString normalBorder = palette.color(QPalette::Button).darker(64).name(QColor::HexArgb);
    QString altBg = palette.color(QPalette::Button).name(QColor::HexArgb);

    setStyleSheet(QString(
        "QTabBar::tab { "
        "  background: %1; "
        "  border: 1px solid %2; "
        "  padding: 5px; "
        "} "
        "QTabBar::tab:selected { "
        "  background: %3; "
        "  border: none;"
        "}"
        )
        .arg(normalBg)
        .arg(normalBorder)
        .arg(altBg)
    );
}

void DraggableTabBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        int index = this->tabAt(event->position().toPoint());

        if (index != -1)
        {
            dragging = true;
            w = qobject_cast<QTabWidget *>(parent())->widget(index);

            QTabBar *tabBar = this;
            QRect tabRect = tabBar->tabRect(index);

            QPixmap pixmap(tabRect.size());
            pixmap.fill(Qt::transparent);

            QPainter painter(&pixmap);
            tabBar->render(&painter, QPoint(), QRegion(tabRect));
            painter.end();

            this->pix = pixmap;

            startPos = event->position().toPoint();
            draggedTabIndex = index;
        }
    }

    QTabBar::mousePressEvent(event);
}

void DraggableTabBar::mouseMoveEvent(QMouseEvent *event)
{
    QRect collision = qobject_cast<QTabWidget *>(parent())->rect();

    if (
        dragging
        && (event->pos() - startPos).manhattanLength() >= QApplication::startDragDistance()
        && !collision.contains(event->position().toPoint()))
    {
        dragging = false;

        emit startDrag(w, startPos, pix);

        QMouseEvent *release = new QMouseEvent(
            QEvent::MouseButtonRelease,
            event->position(),
            event->globalPosition(),
            Qt::LeftButton,
            event->buttons(),
            event->modifiers()
        );

        QCoreApplication::postEvent(this, release);

        event->ignore();
        return;
    }

    QTabBar::mouseMoveEvent(event);
}
