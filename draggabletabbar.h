#ifndef DRAGGABLETABBAR_H
#define DRAGGABLETABBAR_H

#include <QObject>
#include <QTabBar>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QTabWidget>

class DraggableTabBar : public QTabBar
{
    Q_OBJECT
public:
    DraggableTabBar(QWidget *parent = nullptr);

signals:
    void startDrag(QWidget *w, const QPoint &pos, const QPixmap pix);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool dragging;
    QPoint startPos;
    int draggedTabIndex;

    QPixmap pix;
    QWidget *w;
};

#endif // DRAGGABLETABBAR_H
