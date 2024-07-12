#ifndef CLICKMENUPUSHBUTTON_H
#define CLICKMENUPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QString>
#include <QIcon>
#include <QMouseEvent>
#include <QAction>
#include <QPushButton>

class ClickMenuPushButton : public QPushButton
{
    Q_OBJECT
public:
    ClickMenuPushButton(QWidget *parent = nullptr);
    ClickMenuPushButton(const QString &text, QWidget *parent = nullptr);
    ClickMenuPushButton(const QIcon &icon, const QString &text, QWidget *parent=nullptr);

    QAction* newHorizontal();
    QAction* newVertical();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QMenu *contextMenu;
    QAction *actionNewHorizontal;
    QAction *actionNewVertical;

    inline void setupThis();
};

#endif // CLICKMENUPUSHBUTTON_H
