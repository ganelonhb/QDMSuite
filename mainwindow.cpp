#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->menu = this->menuBar();

    this->dock = new DiceDockWidget(&this->dt, this);
    this->dock->hide();
    this->dock->setFloating(true);

    connect(&this->dt, &DiceRollTracker::changed, this, &MainWindow::dice_rolled);

    QHBoxLayout* horizontalLayout = new QHBoxLayout(this->ui->homeTab);

    this->ui->homeTab->setLayout(horizontalLayout);

    this->ui->homeTab->layout()->addWidget(new WelcomeWidget());
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

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    Q_UNUSED(index);

    if (this->ui->tabWidget->count() == 1)
        this->ui->tabWidget->removeTab(0);
}

