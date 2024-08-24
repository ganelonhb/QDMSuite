#ifndef MARKDOWNEDITORWIDGET_H
#define MARKDOWNEDITORWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QWebEngineView>
#include <QWebChannel>
#include <QFile>
#include <QStyle>

#include "markdownwebenginepage.h"
#include "document.h"
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
    Document content;
};

#endif // MARKDOWNEDITORWIDGET_H
