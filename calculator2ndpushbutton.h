#ifndef CALCULATOR2NDPUSHBUTTON_H
#define CALCULATOR2NDPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QPalette>
#include <QFont>
#include <QPoint>
#include <QEvent>
#include <QSvgRenderer>
#include <QFile>
#include <QXmlStreamReader>
#include <QBuffer>
#include <QMessageBox>
#include <QFontMetrics>
#include <QRegularExpression>

#include <algorithm>

class Calculator2ndPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QString secondaryText READ secondaryText WRITE setSecondaryText);
    Q_PROPERTY(QColor secondaryColor READ secondaryColor WRITE setSecondaryColor);
    Q_PROPERTY(QPoint offset READ offset WRITE setOffset);
    Q_PROPERTY(qint32 size READ size WRITE setSize);

public:
    Calculator2ndPushButton(QWidget *parent = nullptr);
    Calculator2ndPushButton(const QString &text1, const QString &text2, QWidget *parent = nullptr);
    Calculator2ndPushButton(const QIcon &icon, const QString &text1, const QString &text2, QWidget *parent = nullptr);

    QString secondaryText() const;
    void setSecondaryText(const QString &text);

    QColor secondaryColor() const;
    void setSecondaryColor(const QColor &color);

    void setSecondaries(const QString &text, const QColor &color);

    QPoint offset() const;
    void setOffset(const QPoint &p);

    qint32 size() const;
    void setSize(qint32 size);

    QSvgRenderer *svgRenderer() const;
    void setSvg(const QString &icon);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    static inline QString changeSvgColor(const QString &svgContent, const QColor &oldColor, const QColor &color);

    QString m_secondaryText;
    QColor m_secondaryColor;
    QSvgRenderer *m_icon{nullptr};

    QPoint m_offset;
    qint32 m_size;
};

#endif // CALCULATOR2NDPUSHBUTTON_H
