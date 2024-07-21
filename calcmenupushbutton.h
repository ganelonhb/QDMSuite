#ifndef CALCMENUPUSHBUTTON_H
#define CALCMENUPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QString>
#include <QAction>
#include <QMenu>
#include <QMap>
#include <QPushButton>
#include <QMouseEvent>

class CalcMenuPushButton : public QPushButton
{
    Q_OBJECT
public:
    CalcMenuPushButton(QWidget *parent = nullptr);
    CalcMenuPushButton(const QString &text, QWidget *parent = nullptr);
    CalcMenuPushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

    void addMenuAction(const QString &name, QAction *action);

    void mousePressEvent(QMouseEvent *event) override;

    QAction *action(const QString &name);
    QAction *operator[](const QString &name);

private:
    QMap<QString, QAction *> map;

    QMenu *menu;
};

#endif // CALCMENUPUSHBUTTON_H
