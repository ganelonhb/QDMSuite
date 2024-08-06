#include "qclickablelabel.h"

QClickableLabel::QClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f)
    , m_hoverColor(Qt::transparent)
    , endColor(Qt::transparent)
{}

QClickableLabel::QClickableLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
    , m_hoverColor(Qt::transparent)
    , endColor(Qt::transparent)
{}

QClickableLabel::QClickableLabel(const QColor &color, const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
    , m_hoverColor(Qt::transparent)
    , endColor(color)
{}

QClickableLabel::~QClickableLabel()
{}

QColor QClickableLabel::hoverColor() const
{
    return m_hoverColor;
}

void QClickableLabel::setHoverColor(const QColor &color)
{
    m_hoverColor = color;
    update();
}

void QClickableLabel::setAnimationColor(const QColor &color)
{
    endColor = color;
}

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

void QClickableLabel::enterEvent(QEnterEvent *event)
{
    startAnimation(Qt::transparent, endColor);
    QLabel::enterEvent(event);
}

void QClickableLabel::leaveEvent(QEvent *event)
{
    startAnimation(endColor, Qt::transparent);
    QLabel::leaveEvent(event);
}

void QClickableLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QBrush(m_hoverColor));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    QLabel::paintEvent(event);
}

inline void QClickableLabel::startAnimation(const QColor &startColor, const QColor &endColor)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "hoverColor");
    animation->setDuration(500);
    animation->setStartValue(startColor);
    animation->setEndValue(endColor);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
