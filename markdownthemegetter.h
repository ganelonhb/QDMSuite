#ifndef MARKDOWNTHEMEGETTER_H
#define MARKDOWNTHEMEGETTER_H

#include <QObject>
#include <QString>

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

class MarkdownThemeGetter : QObject
{
    Q_OBJECT

public:
    MarkdownThemeGetter();

    void setTheme(ThemeName name = ThemeName::NATIVE);
    QString theme() const;

    QString operator()() const;

    static MarkdownThemeGetter getter;

private:
    ThemeName m_theme;
};

#endif // MARKDOWNTHEMEGETTER_H
