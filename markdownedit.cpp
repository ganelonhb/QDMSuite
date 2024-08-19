#include "markdownedit.h"

MarkdownEdit::MarkdownEdit(QWidget *parent)
    : QTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this->document(), &QTextDocument::contentsChanged, this, &MarkdownEdit::updateLineNumberArea);
    connect(this, &MarkdownEdit::cursorPositionChanged, this, &MarkdownEdit::highlightCurrentLine);

    defaultFontSize = font().pointSize();

    updateLineNumberAreaWidth();

    highlighter = new MarkdownHighlighter(this->document());
}

MarkdownEdit::MarkdownEdit(const QString &text, QWidget *parent)
    : QTextEdit(text, parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this->document(), &QTextDocument::contentsChanged, this, &MarkdownEdit::updateLineNumberArea);
    connect(this, &MarkdownEdit::cursorPositionChanged, this, &MarkdownEdit::highlightCurrentLine);

    defaultFontSize = font().pointSize();

    updateLineNumberAreaWidth();
}

void MarkdownEdit::resizeEvent(QResizeEvent *event)
{
    QTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberArea->lineNumberAreaWidth(), cr.height()));
}

void MarkdownEdit::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberArea->lineNumberAreaWidth(), 0, 0, 0);
}

void MarkdownEdit::updateLineNumberArea()
{
    QRect rect = viewport()->rect();

    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth();
    }
}

void MarkdownEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::blue).lighter(130);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);

        QTextCursor cursor = textCursor();
        cursor.clearSelection(); // Clear any existing selection
        selection.cursor = cursor; // Assign the cursor to the selection

        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MarkdownEdit::scrollContentsBy(int dx, int dy)
{
    QTextEdit::scrollContentsBy(dx, dy);
    lineNumberArea->scroll(0, dy);
}

void MarkdownEdit::resetFontSize()
{
    QFont f = font();
    f.setPointSize(defaultFontSize);
    setFont(f);
    lineNumberArea->update();
    updateLineNumberAreaWidth();
}

void MarkdownEdit::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        int numDegrees = event->angleDelta().y() / 8;
        int numSteps = numDegrees / 15;
        QFont f = font();
        int newSize = f.pointSize() + numSteps;
        if (newSize > 4)
        {
            f.setPointSize(newSize);
            setFont(f);
            lineNumberArea->update();
            updateLineNumberAreaWidth();
        }
        event->accept();
        return;
    }

    QTextEdit::wheelEvent(event);
}

void MarkdownEdit::keyReleaseEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal)
        {
            QFont f = font();
            int newSize = f.pointSize() + 1;

            f.setPointSize(newSize);
            setFont(f);
            lineNumberArea->update();
            updateLineNumberAreaWidth();
            event->accept();
            return;
        }

        if (event->key() == Qt::Key_Minus || event->key() == Qt::Key_Underscore)
        {
            QFont f = font();
            int newSize = f.pointSize() - 1;
            if (newSize > 4)
            {
                f.setPointSize(newSize);
                setFont(f);
                lineNumberArea->update();
                updateLineNumberAreaWidth();
            }
            event->accept();
            return;
        }
    }

    QTextEdit::keyPressEvent(event);
}

void MarkdownEdit::focusInEvent(QFocusEvent *event)
{
    QTextEdit::focusInEvent(event);
    highlightCurrentLine();
}

void MarkdownEdit::focusOutEvent(QFocusEvent *event)
{
    QTextEdit::focusOutEvent(event);
    clearLineHighlighting();
}

void MarkdownEdit::clearLineHighlighting()
{
    setExtraSelections(QList<QTextEdit::ExtraSelection>()); // Clear all extra selections
}
