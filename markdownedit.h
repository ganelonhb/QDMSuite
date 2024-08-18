#ifndef MARKDOWNEDIT_H
#define MARKDOWNEDIT_H

#include <QObject>
#include <QHBoxLayout>
#include <QTextEdit>

#include "linenumberarea.h"

class MarkdownEdit : public QTextEdit
{
    Q_OBJECT
public:
    MarkdownEdit(QWidget *parent = nullptr);
    MarkdownEdit(const QString &text, QWidget *parent = nullptr);

    void setMarkdownText(const QString &markdown);
    QString markdownText() const;
    void setSourceMode(bool sourceMode);

    void resetFontSize();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void scrollContentsBy(int dx, int dy) override;

    void keyReleaseEvent(QKeyEvent *event) override {
        QTextEdit::keyReleaseEvent(event);
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            updateLineNumberArea();
        }
    }
private:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea();
    void lineNumberAreaPaintEvent(QPaintEvent *event);

    LineNumberArea *lineNumberArea;
    void highlightCurrentLine();
    int defaultFontSize;
};

#endif // MARKDOWNEDIT_H
