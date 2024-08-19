#include "linenumberarea.h"

LineNumberArea::LineNumberArea(QTextEdit *editor)
    : QWidget{editor}
    , textEdit(editor)
{
    if (editor)
        this->setPalette(textEdit->palette());
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(lineNumberAreaWidth(), textEdit->height());;
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), palette().base().color().darker(64));

    QTextBlock block = textEdit->document()->begin();
    int lineNumber = 1;
    int top = static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).translated(0, -textEdit->verticalScrollBar()->value()).top());
    int bottom = top + static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QTextLayout *layout = block.layout();
            const int lineCount = layout->lineCount();

            for (int i = 0; i < lineCount; ++i)
            {
                QTextLine line = layout->lineAt(i);
                int lineTop = static_cast<int>(line.y()) + top;
                int lineBottom = lineTop + static_cast<int>(line.height());

                if (lineTop >= event->rect().top() && lineBottom <= event->rect().bottom())
                {
                    QString number = QString::number(lineNumber);
                    painter.setPen(textEdit->palette().text().color());
                    painter.drawText(0, lineTop, width(), textEdit->fontMetrics().height(), Qt::AlignCenter, number);

                    ++lineNumber;
                }
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).height());
    }
}

int LineNumberArea::lineNumberAreaWidth() const
{
    int digits = 1;
    int max = qMax(1, textEdit->document()->blockCount());

    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 3 + textEdit->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}
