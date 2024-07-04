#ifndef CONTEXTMENUPUSHBUTTON_H
#define CONTEXTMENUPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QIcon>
#include <QPushButton>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>

class ContextMenuPushButton : public QPushButton
{
    Q_OBJECT
public:
    ContextMenuPushButton(QWidget *parent = nullptr);
    ContextMenuPushButton(const QString &text, QWidget *parent = nullptr);
    ContextMenuPushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

    QAction* newTab();
    QAction* newWindow();
    QAction* newDock();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QMenu *contextMenu;
    QAction *actionNewTab;
    QAction *actionNewWindow;
    QAction *actionNewDock;

    void setupThis();
};

#endif // CONTEXTMENUPUSHBUTTON_H
