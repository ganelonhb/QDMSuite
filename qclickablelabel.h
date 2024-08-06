#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H

#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QPainter>

class QClickableLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor);

public:
    QClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QClickableLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QClickableLabel(const QColor &color, const QString &text = "", QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QClickableLabel();

    QColor hoverColor() const;

    void setHoverColor(const QColor &color);

    void setAnimationColor(const QColor &color);

signals:
    void clicked();
    void pressed();
    void released();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    inline void startAnimation(const QColor &startColor, const QColor &endColor);

    QColor m_hoverColor;
    QColor endColor;
};

#endif // QCLICKABLELABEL_H
