#include "qclickablelabel.h"

QClickableLabel::QClickableLabel(QWidget* parent)
    : QLabel(parent)
{}

QClickableLabel::~QClickableLabel() {}

void QClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit pressed();

    QLabel::mousePressEvent(event);
}

void QClickableLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
        emit released();
    }

    QLabel::mouseReleaseEvent(event);
}
