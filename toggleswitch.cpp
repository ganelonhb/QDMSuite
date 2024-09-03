#include "toggleswitch.h"

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QCheckBox(parent)
    , m_circlePos(5)
    , m_pillColor(palette().light().color())
    , m_newPillColor(palette().accent().color())
    , m_iconOpacity(0.0)
{
    setCheckable(true);

    m_circleAnimation = new QPropertyAnimation(this, "circlePos");
    m_circleAnimation->setDuration(150);

    m_colorAnimation = new QPropertyAnimation(this, "pillColor");
    m_colorAnimation->setDuration(150);

    m_iconOpacityAnimation = new QPropertyAnimation(this, "iconOpacity");
    m_iconOpacityAnimation->setDuration(150);

    connect(this, &QCheckBox::toggled, this, &ToggleSwitch::onToggled);
}

qreal ToggleSwitch::circlePos() const
{
    return m_circlePos;
}

void ToggleSwitch::setCirclePos(qreal pos)
{
    m_circlePos = pos;
    update();
}

QColor ToggleSwitch::pillColor() const
{
    return m_pillColor;
}

void ToggleSwitch::setPillColor(const QColor &color)
{
    m_pillColor = color;
    update();
}

void ToggleSwitch::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    qreal height = this->height() - 10;
    qreal width = this->width() - 10;
    QRectF pillRect(5, 5, width, height);
    qreal circleDiameter = height;
    QRectF circleRect(m_circlePos, 5, circleDiameter, circleDiameter);

    painter.setBrush(m_pillColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(pillRect, height / 2, height / 2);

    QColor circleColor = palette().button().color();
    QColor borderColor = palette().midlight().color();

    painter.setPen(QPen(borderColor, 1));

    painter.setBrush(circleColor);
    painter.drawEllipse(circleRect);

    if (!m_icon.isNull())
    {
        painter.setOpacity(m_iconOpacity);
        QPixmap pixmap = m_icon.pixmap(QSize(circleDiameter - 4, circleDiameter - 4));
        QRectF iconRect(circleRect.x() + 4, circleRect.y() + 4, circleDiameter - 8, circleDiameter - 8);
        painter.drawPixmap(iconRect.toRect(), pixmap);
        painter.setOpacity(1.0);
    }

    if (!isEnabled()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 80));
        painter.drawRoundedRect(pillRect, height / 2, height / 2);
        painter.setPen(QPen(QColor(0, 0, 0, 80), 1));
        painter.drawEllipse(circleRect);
    }

    event->accept();
}

void ToggleSwitch::onToggled(bool checked)
{
    m_circleAnimation->setStartValue(m_circlePos);
    m_circleAnimation->setEndValue(checked ? width() - height() + 5: 5);

    m_colorAnimation->setStartValue(m_pillColor);
    m_colorAnimation->setEndValue(checked ? m_newPillColor : palette().light().color());

    m_iconOpacityAnimation->setStartValue(m_iconOpacity);
    m_iconOpacityAnimation->setEndValue(checked ? 1.0 : 0.0);

    m_circleAnimation->start();
    m_colorAnimation->start();
    m_iconOpacityAnimation->start();
}


QIcon ToggleSwitch::icon() const
{
    return m_icon;
}

void ToggleSwitch::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}


QColor ToggleSwitch::newPillColor() const
{
    return m_newPillColor;
}

void ToggleSwitch::setNewPillColor(const QColor &color)
{
    m_newPillColor = color;
    update();
}


qreal ToggleSwitch::iconOpacity() const
{
    return m_iconOpacity;
}

void ToggleSwitch::setIconOpacity(qreal opacity)
{
    m_iconOpacity = opacity;
    update();
}
