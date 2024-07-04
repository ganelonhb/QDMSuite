#include "contextmenupushbutton.h"

ContextMenuPushButton::ContextMenuPushButton(QWidget *parent)
    : QPushButton(parent)
{
    setupThis();
}

ContextMenuPushButton::ContextMenuPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setupThis();
}

ContextMenuPushButton::ContextMenuPushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    setupThis();
}

void ContextMenuPushButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        this->contextMenu->exec(event->globalPosition().toPoint());
    }
    else
    {
        QPushButton::mousePressEvent(event);
    }
}

QAction* ContextMenuPushButton::newTab()
{
    return this->actionNewTab;
}

QAction* ContextMenuPushButton::newWindow()
{
    return this->actionNewWindow;
}

QAction* ContextMenuPushButton::newDock()
{
    return this->actionNewDock;
}

void ContextMenuPushButton::setupThis()
{
    this->contextMenu = new QMenu(this);

    this->actionNewDock = new QAction("Add Dock Widget", this);
    this->actionNewTab = new QAction("Add New Tab", this);
    this->actionNewWindow = new QAction("Add New Window", this);

    this->contextMenu->addAction(this->actionNewTab);
    this->contextMenu->addAction(this->actionNewWindow);
    this->contextMenu->addAction(this->actionNewDock);
}
