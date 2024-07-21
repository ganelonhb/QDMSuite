#include "calcmenupushbutton.h"

CalcMenuPushButton::CalcMenuPushButton(QWidget *parent)
    : QPushButton(parent)
{
    this->menu = new QMenu(this);
}

CalcMenuPushButton::CalcMenuPushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    this->menu = new QMenu(this);
}

CalcMenuPushButton::CalcMenuPushButton(const QIcon &icon, const QString &text, QWidget *parent)
    :QPushButton(icon, text, parent)
{
    this->menu = new QMenu(this);
}

void CalcMenuPushButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->menu->exec(event->globalPosition().toPoint());
        QPushButton::mousePressEvent(event);
    }
}

void CalcMenuPushButton::addMenuAction(const QString &name, QAction *action)
{
    if (action->parent() != this)
        action->setParent(this);

    map.insert(name, action);
    menu->addAction(action);
}

QAction *CalcMenuPushButton::action(const QString &name)
{
    return map[name];
}

QAction *CalcMenuPushButton::operator[](const QString &name)
{
    return map[name];
}
