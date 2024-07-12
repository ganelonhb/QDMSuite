#include "clickmenupushbutton.h"

ClickMenuPushButton::ClickMenuPushButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setupThis();
}

ClickMenuPushButton::ClickMenuPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    this->setupThis();
}

ClickMenuPushButton::ClickMenuPushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    this->setupThis();
}


QAction* ClickMenuPushButton::newHorizontal()
{
    return this->actionNewHorizontal;
}

QAction* ClickMenuPushButton::newVertical()
{
    return this->actionNewVertical;
}

void ClickMenuPushButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->contextMenu->exec(event->globalPosition().toPoint());
        QPushButton::mousePressEvent(event);
    }
}

inline void ClickMenuPushButton::setupThis()
{
    this->contextMenu = new QMenu(this);

    this->actionNewHorizontal = new QAction("Split Horizontal", this);
    this->actionNewVertical = new QAction("Split Vertical", this);

    this->contextMenu->addAction(this->actionNewHorizontal);
    this->contextMenu->addAction(this->actionNewVertical);
}
