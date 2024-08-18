#ifndef MARKDOWNEDITORWIDGET_H
#define MARKDOWNEDITORWIDGET_H

#include <QWidget>
#include "qdmswidget.hpp"

namespace Ui {
class MarkdownEditorWidget;
}

class MarkdownEditorWidget : public QDMSWidget
{
    Q_OBJECT

public:
    explicit MarkdownEditorWidget(QWidget *parent = nullptr);
    ~MarkdownEditorWidget();

private:
    Ui::MarkdownEditorWidget *ui;
};

#endif // MARKDOWNEDITORWIDGET_H
