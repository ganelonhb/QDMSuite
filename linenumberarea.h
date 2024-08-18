#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QTextEdit>
#include <QSize>
#include <QPaintEvent>
#include <QPainter>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(QTextEdit *editor = nullptr);
    QSize sizeHint() const override;

    int lineNumberAreaWidth() const;

protected:
    void paintEvent(QPaintEvent * event) override;

private:
    QTextEdit *textEdit;
};

#endif // LINENUMBERAREA_H
