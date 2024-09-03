#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QCheckBox>
#include <QObject>
#include <QPropertyAnimation>
#include <QPainter>
#include <QColor>
#include <QPaintEvent>
#include <QIcon>
#include <QPixmap>

class ToggleSwitch : public QCheckBox
{
    Q_OBJECT
    Q_PROPERTY(qreal circlePos READ circlePos WRITE setCirclePos)
    Q_PROPERTY(QColor pillColor READ pillColor WRITE setPillColor)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(double iconOpacity READ iconOpacity WRITE setIconOpacity)

public:
    ToggleSwitch(QWidget *parent = nullptr);

    qreal circlePos() const;
    void setCirclePos(qreal pos);

    QColor pillColor() const;
    void setPillColor(const QColor &color);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QColor newPillColor() const;
    void setNewPillColor(const QColor &color);

    double iconOpacity() const;
    void setIconOpacity(qreal opacity);

protected:
    void paintEvent(QPaintEvent * event) override;

private slots:
    void onToggled(bool checked);

private:
    qreal m_circlePos;
    QColor m_pillColor;
    QColor m_newPillColor;
    QPropertyAnimation *m_circleAnimation;
    QPropertyAnimation *m_colorAnimation;
    QPropertyAnimation *m_iconOpacityAnimation;
    QIcon m_icon;
    qreal m_iconOpacity;
};

#endif // TOGGLESWITCH_H
