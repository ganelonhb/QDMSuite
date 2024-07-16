#ifndef DRAGGABLETABWIDGET_H
#define DRAGGABLETABWIDGET_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QPoint>
#include <QApplication>
#include <QRect>
#include <QPixmap>
#include <QMetaType>
#include <QVariant>
#include <QByteArray>
#include <QDataStream>
#include <QtTypes>
#include <QMessageBox>

#include "draggabletabbar.h"

class DraggableTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    DraggableTabWidget(QWidget *parent = nullptr);

signals:
    void dropRemoveEvent();
    void dropAccepted();

protected slots:
    void onStartDrag(QWidget *w, const QPoint &pos, const QPixmap pix);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    static inline QByteArray serializePtr(QObject * obj);
    static inline QObject *deserializePtr(const QByteArray& byteArray);
};

Q_DECLARE_METATYPE(DraggableTabWidget *);

#endif // DRAGGABLETABWIDGET_H
