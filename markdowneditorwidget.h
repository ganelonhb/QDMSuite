#ifndef MARKDOWNEDITORWIDGET_H
#define MARKDOWNEDITORWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QWebEngineView>
#include <QWebChannel>
#include <QFile>
#include <QStyle>
#include <QPropertyAnimation>

#include "markdownwebenginepage.h"
#include "markdownthemegetter.h"
#include "document.h"
#include "qdmswidget.hpp"
#include "triswitch.h"

namespace Ui {
class MarkdownEditorWidget;
}

class MarkdownEditorWidget : public QDMSWidget
{
    Q_OBJECT

public:
    explicit MarkdownEditorWidget(QWidget *parent = nullptr);
    ~MarkdownEditorWidget();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);
    void cssChanged();
    void textChanged();

    void modeChanged(TriSwitchPosition pos);

    void on_zoomSlider_sliderMoved(int position);

    void on_resetFactor_clicked();

    void on_zoomDown_clicked();

    void on_zoomUp_clicked();

private:
    Ui::MarkdownEditorWidget *ui;
    Document content;

    MarkdownThemeGetter theme;
};

#endif // MARKDOWNEDITORWIDGET_H
