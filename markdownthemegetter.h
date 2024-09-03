#ifndef MARKDOWNTHEMEGETTER_H
#define MARKDOWNTHEMEGETTER_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QPalette>
#include <QApplication>
#include <QFont>
#include <QFontInfo>
#include <QFile>

enum class ThemeName
{
    NATIVE,
    DARK,
    LIGHT,
    HIGHCONTRAST,
    FIVE_E,
    CHERRY_THRILL,
    LAMBDA_COMPLEX,
};

class MarkdownThemeGetter : public QObject
{
    Q_OBJECT

public:
    MarkdownThemeGetter(QObject *parent = nullptr);

    QString theme() const;
    QString url() const;
    QColor bgColor() const;

    QString operator()();

signals:
    void themeChanged();

public slots:
    void setTheme(const QString &name = "native", const QString &url = QString());

private:
    QString m_theme;
    QString m_url;
    QColor bg;

    QString colorFix(const QColor &color) const;
};

#endif // MARKDOWNTHEMEGETTER_H
