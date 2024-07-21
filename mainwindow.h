#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QGridLayout>

#include "dicerolltracker.h"
#include "dicerollwidget.h"
#include "fantasynamegeneratorwidget.h"
#include "welcomewidget.h"

#include "calculatorwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class WidgetType {
        WINDOW,
        TAB,
        FLOATING_DOCK,
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void dice_rolled();

    void on_diceRollerToolButton_clicked();

    void newDiceRollerTab();
    void newDiceRollerWindow();
    void newDiceRollerDock();

    void newFNGTab();
    void newFNGWindow();
    void newFNGDock();

    void on_fantasyNameGenerator_clicked();

    void newWidget(QWidget *widget, WidgetType wt = WidgetType::WINDOW, const QString &title = "Q.D.M.S.");

    void unlockTabSplit();
    void lockTabSplit();

    void on_actionDice_Roller_2_triggered();

    void on_actionName_Generator_triggered();

private:
    Ui::MainWindow *ui;

    DiceRollTracker dt;

    const QMenuBar* menu;

};
#endif // MAINWINDOW_H
