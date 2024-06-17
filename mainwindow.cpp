#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->dock = new DiceDockWidget(&this->dt, this);

    this->dock->setFloating(true);
    this->dock->hide();

    connect(&this->dt, &DiceRollTracker::changed, this, &MainWindow::dice_rolled);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDice_Roller_triggered()
{
    this->dock->show();
}

void MainWindow::dice_rolled()
{
    if (!this->dt.empty()) {
        const DiceRoll roll= this->dt.last();
        const QString message = "Last Roll - 1d" + QString::number(roll.sides()) + " : " + QString::number(roll.result());
        this->ui->statusbar->showMessage(message);
    }
}
