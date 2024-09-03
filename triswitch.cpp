#include "triswitch.h"

TriSwitch::TriSwitch(QWidget *parent)
    : QPushButton(parent)
    , m_position(TriSwitchPosition::MIDDLE)
{
    setCheckable(true);

    m_circlePos = ((width() - height()) / 2) + 2.5;
    m_leftColor = palette().accent().color();

    float h, s, v;
    m_leftColor.getHsvF(&h, &s, &v);
    h = fmodf(h + .5f, 1.f);

    m_rightColor.setHsvF(h,s,v);

    m_circleAnimation = new QPropertyAnimation(this, "circlePos");
    m_circleAnimation->setDuration(150);
}

qreal TriSwitch::circlePos() const
{
    return m_circlePos;
}

void TriSwitch::setCirclePos(qreal pos)
{
    m_circlePos = pos;
    update();
}

void TriSwitch::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    qreal height = this->height() - 10;
    qreal width = this->width() - 10;
    QRectF pillRect(5, 5, width, height);
    qreal circleDiameter = height;
    QRectF circleRect(m_circlePos, 5, circleDiameter, circleDiameter);

    QPainterPath pillPath;
    pillPath.addRoundedRect(pillRect, height / 2, height / 2);

    painter.setClipPath(pillPath);

    if (m_leftColor.isValid()) {
        QRectF leftColorRect(5, 5, m_circlePos + circleDiameter / 2, height);
        painter.setBrush(m_leftColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(leftColorRect);
    }

    if (m_rightColor.isValid()) {
        QRectF rightColorRect(m_circlePos + circleDiameter / 2, 5, width, height);
        painter.setBrush(m_rightColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rightColorRect);
    }

    if (!m_leftIcon.isNull()) {
        QPixmap leftPixmap = m_leftIcon.pixmap(QSize(circleDiameter - 4, circleDiameter - 4));
        QRectF iconRect(m_circlePos - ((circleDiameter / 2) + 14), circleRect.y() + 2, circleDiameter - 4, circleDiameter - 4);
        painter.drawPixmap(iconRect.toRect(), leftPixmap);
    }

    if (!m_rightIcon.isNull()) {
        QPixmap rightPixmap = m_rightIcon.pixmap(QSize(circleDiameter - 4, circleDiameter - 4));
        QRectF iconRect(m_circlePos + ((circleDiameter / 2) + 14), circleRect.y() + 2, circleDiameter - 4, circleDiameter - 4);
        painter.drawPixmap(iconRect.toRect(), rightPixmap);
    }

    painter.setClipRect(rect());
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(palette().midlight().color(), 1));
    painter.drawRoundedRect(pillRect, height / 2, height / 2);

    QColor circleColor = palette().button().color();
    QColor borderColor = palette().midlight().color();

    painter.setPen(QPen(borderColor, 1));

    painter.setBrush(circleColor);
    painter.drawEllipse(circleRect);
    if (!isEnabled()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 80));
        painter.drawRoundedRect(pillRect, height / 2, height / 2);
        painter.setPen(QPen(QColor(0, 0, 0, 80), 1));
        painter.drawEllipse(circleRect);
    }

    event->accept();
}

void TriSwitch::mousePressEvent(QMouseEvent *event)
{
    qreal buttonWidth = width();
    qreal third = buttonWidth / 3;

    TriSwitchPosition newPosition;

    if (event->pos().x() < third)
    {
        newPosition = TriSwitchPosition::LEFT;
    }
    else if (event->pos().x() < 2 * third)
    {
        newPosition = TriSwitchPosition::MIDDLE;
    }
    else
    {
        newPosition = TriSwitchPosition::RIGHT;
    }

    if (newPosition == m_position)
    {
        wiggle();
    }
    else
    {
        moveToPosition(newPosition);
    }

    QPushButton::mousePressEvent(event);
}

void TriSwitch::moveToPosition(TriSwitchPosition position)
{
    m_position = position;

    qreal targetPos = 0.;

    switch(position)
    {
    case TriSwitchPosition::LEFT:
        targetPos = 5;
        break;
    case TriSwitchPosition::MIDDLE:
        targetPos = ((width() - height()) / 2) + 2.5;
        break;
    case TriSwitchPosition::RIGHT:
        targetPos = width() - height() + 5;
        break;
    }

    m_circleAnimation->setStartValue(m_circlePos);
    m_circleAnimation->setEndValue(targetPos);

    m_circleAnimation->start();
    //emit positionChanged(position);

    connect(m_circleAnimation, &QPropertyAnimation::finished, [this, position]{emit this->positionChanged(position);});
}

void TriSwitch::wiggle()
{
    qreal originalPos = m_circlePos;
    qreal wiggleDistance = 3.0 + QRandomGenerator::global()->generateDouble();

    QPropertyAnimation *wiggleAnimation = new QPropertyAnimation(this, "circlePos");
    wiggleAnimation->setDuration(100);
    wiggleAnimation->setKeyValueAt(0, originalPos);
    wiggleAnimation->setKeyValueAt(0.25, originalPos + wiggleDistance);
    wiggleAnimation->setKeyValueAt(0.5, originalPos - wiggleDistance);
    wiggleAnimation->setKeyValueAt(0.75, originalPos + wiggleDistance);
    wiggleAnimation->setKeyValueAt(1, originalPos);
    wiggleAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void TriSwitch::setColors(const QColor &left, const QColor &right)
{
    m_leftColor = left;
    m_rightColor = right;

    update();
}

void TriSwitch::setIcons(const QIcon &left, const QIcon &right)
{
    m_leftIcon = left;
    m_rightIcon = right;

    update();
}

TriSwitchPosition TriSwitch::position() const
{
    return m_position;
}
