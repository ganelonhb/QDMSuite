#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>

#include "dicerolltracker.h"
#include "dicedockwidget.h"

#include "welcomewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDice_Roller_triggered();

    void dice_rolled();

private:
    Ui::MainWindow *ui;

    DiceRollTracker dt;

    DiceDockWidget *dock;

    const QMenuBar* menu;

    WelcomeWidget *w;
};
#endif // MAINWINDOW_H
