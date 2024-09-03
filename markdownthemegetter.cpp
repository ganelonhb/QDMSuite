#include "markdownthemegetter.h"

#include <iostream>

MarkdownThemeGetter::MarkdownThemeGetter(QObject *parent)
    : QObject(parent)
{
    m_theme = "native";
    m_url = ":/ui/qmarkdown/markdown.qss";

    QPalette palette = QApplication::palette();
    bg = palette.color(QPalette::Base);

}

void MarkdownThemeGetter::setTheme(const QString &themeName, const QString &url)
{
    m_theme = themeName.toLower().simplified();
    m_url = url;

    emit themeChanged();
}


QString MarkdownThemeGetter::theme() const
{
    return m_theme;
}

QString MarkdownThemeGetter::url() const
{
    return m_url;
}

QString MarkdownThemeGetter::operator()()
{
    if (m_theme == "native")
    {
        QPalette palette = QApplication::palette();
        bg = palette.color(QPalette::Base);

        QString button = colorFix(palette.color(QPalette::Button));
        QString buttonText = colorFix(palette.color(QPalette::ButtonText));

        QString bgString = colorFix(bg.name(QColor::HexArgb));

        QColor textColor(palette.color(QPalette::Text));
        QString defaultText = colorFix(textColor);

        QColor linkColor(palette.color(QPalette::Link));
        QColor linkVisitedColor(palette.color(QPalette::LinkVisited));
        QString link = colorFix(linkColor);
        QString linkVisited = colorFix(linkVisitedColor);

        QColor accentColor(palette.color(QPalette::Accent));
        QString accent = colorFix(accentColor);

        QColor inputColor(palette.color(QPalette::Base));
        QString input = colorFix(inputColor);

        QColor inputTextColor(palette.color(QPalette::Text));
        QString inputText = colorFix(inputTextColor);

        QColor inputBorderColor(palette.color(QPalette::Mid));
        QString inputBorder = colorFix(inputBorderColor);

        QFont font = QApplication::font();
        QFontInfo fontInfo(font);
        QString fontName = fontInfo.family();

        QFile qss(":/ui/qmarkdown/markdown.qss");
        if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Somehow, we could not read the qrc file!";

        QString qssText = QString(qss.readAll())
            .replace("<BACKGROUND_COLOR>", bgString)
            .replace("<DEFAULT_TEXT>", defaultText)
            .replace("<H1_TEXT>", defaultText)
            .replace("<H2_TEXT>", defaultText)
            .replace("<H3_TEXT>", defaultText)
            .replace("<H4_TEXT>", defaultText)
            .replace("<H5_TEXT>", defaultText)
            .replace("<H6_TEXT>", defaultText)
            .replace("<QUOTE_TEXT>", defaultText)
            .replace("<HR_TEXT>", defaultText)
            .replace("<FONT>", fontName)
            .replace("<BLOCK_QUOTE_CITE>", accent)
            .replace("<LINK>", link)
            .replace("<LINK_VISITED>", linkVisited)
            .replace("<BLOCK_QUOTE_COLOR>", accent)
            .replace("<INPUT_BG>", input)
            .replace("<INPUT_TEXT>", inputText)
            .replace("<INPUT_BORDER>", inputBorder)
            .replace("<FOCUS_COLOR>", accent)
            .replace("<RADIO_CHECKBOX>", accent)
            .replace("<BUTTON_BG>", button)
            .replace("<BUTTON_TEXT>", buttonText)
            .replace("<BUTTON_BORDER>", inputBorder);
        qss.close();

        return qssText;
    }
    else if (m_theme == "dark")
    {
        bg = QColor(49, 58, 74);

        QFont font = QApplication::font();
        QFontInfo fontInfo(font);
        QString fontName = fontInfo.family();

        QFile qss(":/ui/qmarkdown/dark.qss");
        if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Somehow, we could not read the qrc file!";

        QString qssText = QString(qss.readAll())
            .replace("<NATIVE_FONT>", fontName);
        qss.close();

        return qssText;
    }
    else if (m_theme == "light")
    {
        bg = QColor(255, 255, 255);

        QFont font = QApplication::font();
        QFontInfo fontInfo(font);
        QString fontName = fontInfo.family();

        QFile qss(":/ui/qmarkdown/light.qss");
        if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Somehow, we could not read the qrc file!";

        QString qssText = QString(qss.readAll())
            .replace("<NATIVE_FONT>", fontName);
        qss.close();

        return qssText;
    }
    else if (m_theme == "high contrast")
    {
        bg = QColor(0, 0, 0);

        QFont font = QApplication::font();
        QFontInfo fontInfo(font);
        QString fontName = fontInfo.family();

        QFile qss(":/ui/qmarkdown/highcontrast.qss");
        if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Somehow, we could not read the qrc file!";

        QString qssText = QString(qss.readAll())
            .replace("<NATIVE_FONT>", fontName);

        qss.close();

        return qssText;
    }
    else if (m_theme == "five e")
    {
        bg = QColor(238, 229, 206);

        QFile qss(":/ui/qmarkdown/5e.qss");
        if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Somehow, we could not read the qrc file!";

        QString qssText = QString(qss.readAll());

        qss.close();
        return qssText;
    }
    else if (m_theme == "lambda complex")
    {
        bg = QColor(41, 41, 41);

        QFont font = QApplication::font();
        QFontInfo fontInfo(font);
        QString fontName = fontInfo.family();

        QFile qss(":/ui/qmarkdown/lambdacomplex.qss");
        if (!qss.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Somehow, we could not read the qrc file!";

        QString qssText = QString(qss.readAll())
            .replace("<NATIVE_FONT>", fontName);
        qss.close();

        return qssText;
    }

    bg = QColor(255,255,255);
    return QString();
}

QColor MarkdownThemeGetter::bgColor() const
{
    return bg;
}

QString MarkdownThemeGetter::colorFix(const QColor &color) const
{
    QString s = color.name(QColor::HexArgb);

    return QString("#%1%2%3%4").arg(s.mid(3, 2), s.mid(5, 2), s.mid(7, 2), s.mid(1, 2));
};
