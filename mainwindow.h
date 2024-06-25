#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>

#include "dicerolltracker.h"
#include "dicedockwidget.h"
#include "fantasynamegeneratorwidget.h"

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

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;

    DiceRollTracker dt;

    DiceDockWidget *dock;

    const QMenuBar* menu;

};
#endif // MAINWINDOW_H
