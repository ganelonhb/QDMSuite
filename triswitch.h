#ifndef TRISWITCH_H
#define TRISWITCH_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QPainter>
#include <QMouseEvent>
#include <QIcon>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QRandomGenerator>

enum class TriSwitchPosition
{
    LEFT = -1,
    MIDDLE = 0,
    RIGHT = 1
};

class TriSwitch : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal circlePos READ circlePos WRITE setCirclePos)

public:
    TriSwitch(QWidget *parent = nullptr);

    qreal circlePos() const;
    void setCirclePos(qreal pos);
    void setColors(const QColor &left, const QColor &right);

    void setIcons(const QIcon &left, const QIcon &right);
    TriSwitchPosition position() const;

signals:
    void positionChanged(TriSwitchPosition pos);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moveToPosition(TriSwitchPosition position);
    void wiggle();

private:
    qreal m_circlePos;
    QPropertyAnimation *m_circleAnimation;
    QIcon m_leftIcon;
    QIcon m_rightIcon;
    QColor m_leftColor;
    QColor m_rightColor;
    TriSwitchPosition m_position;
};

#endif // TRISWITCH_H
