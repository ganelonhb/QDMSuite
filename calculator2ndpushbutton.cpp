#include "calculator2ndpushbutton.h"

#include <iostream>

Calculator2ndPushButton::Calculator2ndPushButton(QWidget *parent)
    : QPushButton(parent)
    , m_secondaryColor(palette().color(QPalette::ButtonText))
    , m_offset(3, 10)
    , m_size(2)
{}

Calculator2ndPushButton::Calculator2ndPushButton(const QString &text1, const QString &text2, QWidget *parent)
    : QPushButton(text1, parent)
    , m_secondaryText(text2)
    , m_secondaryColor(palette().color(QPalette::ButtonText))
    , m_offset(3, 10)
    , m_size(2)
{}

Calculator2ndPushButton::Calculator2ndPushButton(const QIcon &icon, const QString &text1, const QString &text2, QWidget *parent)
    : QPushButton(icon, text1, parent)
    , m_secondaryText(text2)
    , m_secondaryColor(palette().color(QPalette::ButtonText))
    , m_offset(3, 10)
    , m_size(2)
{}

QString Calculator2ndPushButton::secondaryText() const
{
    return m_secondaryText;
}

void Calculator2ndPushButton::setSecondaryText(const QString &text)
{
    m_secondaryText = text;
}

QColor Calculator2ndPushButton::secondaryColor() const
{
    return m_secondaryColor;
}

void Calculator2ndPushButton::setSecondaryColor(const QColor &color)
{
    m_secondaryColor = color;
}

void Calculator2ndPushButton::setSecondaries(const QString &text, const QColor &color)
{
    m_secondaryText = text;
    m_secondaryColor = color;
}

QPoint Calculator2ndPushButton::offset() const
{
    return m_offset;
}

void Calculator2ndPushButton::setOffset(const QPoint &p)
{
    m_offset = p;
}

qint32 Calculator2ndPushButton::size() const
{
    return m_size;
}

void Calculator2ndPushButton::setSize(qint32 size)
{
    m_size = size;
}


void Calculator2ndPushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    if (!m_secondaryText.isEmpty() && !m_icon)
    {
        QPainter painter(this);
        painter.setPen(m_secondaryColor);

        QFont secondaryFont = font();

        int pixelSize = secondaryFont.pixelSize();
        int pointSize = secondaryFont.pointSize();

        if (pointSize != -1)
            secondaryFont.setPointSize(std::max(pointSize - m_size, 1));
        else
            secondaryFont.setPixelSize(std::max(pixelSize - m_size, 1));

        painter.setFont(secondaryFont);

        painter.drawText(m_offset, m_secondaryText);
    }
    else if (m_icon && m_icon->isValid())
    {
        QFontMetrics metrics(font());
        int glyphHeight = metrics.height();
        int svgHeight = glyphHeight - m_size;

        QSize defaultSize = m_icon->defaultSize();
        double aspectRatio = static_cast<double>(defaultSize.width() / defaultSize.height());
        int svgWidth = static_cast<int>((svgHeight * aspectRatio) + 0.4);

        QPixmap pix(svgWidth, svgHeight);
        pix.fill(Qt::transparent);

        QPainter pixPaint(&pix);
        m_icon->render(&pixPaint, QRect(0,0,svgWidth, svgHeight));

        QPainter buttonPainter(this);
        buttonPainter.drawPixmap(m_offset, pix);
    }
}

inline QString Calculator2ndPushButton::changeSvgColor(const QString &svgContent, const QColor &oldColor, const QColor &color)
{
    QXmlStreamReader reader(svgContent);
    QString modifiedSvgContent;
    QXmlStreamWriter writer(&modifiedSvgContent);

    QString oldColorFull = oldColor.name();
    QString oldColorShort = oldColor.name().mid(0,4);

    while (!reader.atEnd())
    {
        reader.readNext();

        if (reader.isStartElement() && reader.name().toString() == "path")
        {
            writer.writeStartElement(reader.name().toString());
            foreach(const QXmlStreamAttribute &attr, reader.attributes())
            {
                if (attr.name().toString() == "fill")
                {
                    QString fillValue = attr.value().toString();
                    if (fillValue == oldColorFull || fillValue == oldColorShort)
                    {
                        writer.writeAttribute(attr.name().toString(), color.name());
                    }
                    else
                    {
                        writer.writeAttribute(attr.name().toString(), fillValue);
                    }
                }
                else if (attr.name().toString() == "style")
                {
                    QString styleValue = attr.value().toString();
                    QRegularExpression fullRegExp("fill:" + oldColorFull);
                    QRegularExpression shortRegExp("fill:" + oldColorShort);

                    if(styleValue.contains(fullRegExp) || styleValue.contains(shortRegExp))
                    {
                        styleValue.replace(fullRegExp, "fill:" + color.name());
                        styleValue.replace(shortRegExp, "fill:" + color.name());
                    }

                    writer.writeAttribute(attr.name().toString(), styleValue);
                }
                else
                {
                    writer.writeAttribute(attr.name().toString(), attr.value().toString());
                }
            }
        }
        else
        {
            writer.writeCurrentToken(reader);
        }
    }

    return modifiedSvgContent;
}

void setSvg(const QString &icon);

QSvgRenderer *Calculator2ndPushButton::svgRenderer() const
{
    return m_icon;
}

void Calculator2ndPushButton::setSvg(const QString &icon)
{
    m_icon = new QSvgRenderer(this);
    QFile icn = QFile(icon);

    if (!icn.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Could Not Find Resource", "Could not find the requested resource.");
        return;
    }

    QString svgContent = icn.readAll();
    icn.close();

    svgContent = changeSvgColor(svgContent, Qt::white, m_secondaryColor);
    QByteArray byteArray = svgContent.toUtf8();

    m_icon->load(byteArray);
}
