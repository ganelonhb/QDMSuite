#include "markdowneditorwidget.h"
#include "ui_markdowneditorwidget.h"

MarkdownEditorWidget::MarkdownEditorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MarkdownEditorWidget)
{
    ui->setupUi(this);
}

MarkdownEditorWidget::~MarkdownEditorWidget()
{
    delete ui;
}
