#include "markdownthemegetter.h"

MarkdownThemeGetter::MarkdownThemeGetter() {}

void MarkdownThemeGetter::setTheme(ThemeName name)
{
    m_theme = name;
}

QString MarkdownThemeGetter::theme() const
{
    switch (m_theme)
    {
    case ThemeName::NATIVE:
        return "native";
    case ThemeName::DARK:
        return "dark";
    case ThemeName::LIGHT:
        return "light";
    case ThemeName::HIGHCONTRAST:
        return "highcontrast";
    case ThemeName::FIVE_E:
        return "five e";
    case ThemeName::CHERRY_THRILL:
        return "cherry thrill";
    case ThemeName::LAMBDA_COMPLEX:
        return "lambda complex";
    }
}

QString MarkdownThemeGetter::operator()() const
{

}
