#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->dock = new DiceDockWidget(&this->dt, this);

    this->dock->setFloating(true);
    this->dock->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
