#ifndef MARKDOWNEDITORWIDGET_H
#define MARKDOWNEDITORWIDGET_H

#include <QWidget>

namespace Ui {
class MarkdownEditorWidget;
}

class MarkdownEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MarkdownEditorWidget(QWidget *parent = nullptr);
    ~MarkdownEditorWidget();

private:
    Ui::MarkdownEditorWidget *ui;
};

#endif // MARKDOWNEDITORWIDGET_H
