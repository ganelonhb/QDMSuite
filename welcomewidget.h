#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include "qdmswidget.hpp"

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QDMSWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
