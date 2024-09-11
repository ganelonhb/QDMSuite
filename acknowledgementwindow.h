#ifndef ACKNOWLEDGEMENTWINDOW_H
#define ACKNOWLEDGEMENTWINDOW_H

#include <QWidget>
#include <QFile>
#include <QDesktopServices>
#include <QScrollBar>

namespace Ui {
class AcknowledgementWindow;
}

class AcknowledgementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AcknowledgementWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~AcknowledgementWindow();

private slots:
    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_docs_linkActivated(const QString &link);

private:
    Ui::AcknowledgementWindow *ui;
};

#endif // ACKNOWLEDGEMENTWINDOW_H
