#ifndef ACKNOWLEDGEMENTWINDOW_H
#define ACKNOWLEDGEMENTWINDOW_H

#include <QWidget>

namespace Ui {
class AcknowledgementWindow;
}

class AcknowledgementWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AcknowledgementWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~AcknowledgementWindow();

private:
    Ui::AcknowledgementWindow *ui;
};

#endif // ACKNOWLEDGEMENTWINDOW_H
