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

    painter.fillRect(event->rect(), palette().base().color().darker(32));

    QTextBlock block = textEdit->document()->begin();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).translated(0, -textEdit->verticalScrollBar()->value()).top());
    int bottom = top + static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(textEdit->palette().text().color());
            painter.drawText(0, top, width(), textEdit->fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(textEdit->document()->documentLayout()->blockBoundingRect(block).height());
        ++blockNumber;
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
