#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    this->menu = this->menuBar();

    connect(&this->dt, &DiceRollTracker::changed, this, &MainWindow::dice_rolled);

    connect(this->ui->diceRollerToolButton->newDock(), &QAction::triggered, this, &MainWindow::newDiceRollerDock);
    connect(this->ui->diceRollerToolButton->newWindow(), &QAction::triggered, this, &MainWindow::newDiceRollerWindow);
    connect(this->ui->diceRollerToolButton->newTab(), &QAction::triggered, this, &MainWindow::newDiceRollerTab);

    connect(this->ui->fantasyNameGenerator->newDock(), &QAction::triggered, this, &MainWindow::newFNGDock);
    connect(this->ui->fantasyNameGenerator->newWindow(), &QAction::triggered, this, &MainWindow::newFNGWindow);
    connect(this->ui->fantasyNameGenerator->newTab(), &QAction::triggered, this, &MainWindow::newFNGTab);


    QHBoxLayout* horizontalLayout = new QHBoxLayout(this->ui->homeTab);
    this->ui->homeTab->setLayout(horizontalLayout);
    this->ui->homeTab->layout()->addWidget(new WelcomeWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
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
    this->ui->tabWidget->widget(index)->deleteLater();

    if (this->ui->tabWidget->count() == 1) {
        this->ui->tabWidget->removeTab(0);
        QWidget *tab = new QWidget(this);
        WelcomeWidget *home = new WelcomeWidget();
        QHBoxLayout* horizontalLayout = new QHBoxLayout(tab);

        tab->setLayout(horizontalLayout);

        tab->layout()->addWidget(home);
        this->ui->tabWidget->addTab(tab, "Home");
    }
}


void MainWindow::on_diceRollerToolButton_clicked()
{
    newDiceRollerDock();
}

void MainWindow::newDiceRollerTab()
{
    QWidget *tab = new QWidget(this);
    DiceRollWidget *diceRoll = new DiceRollWidget(&dt, tab);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(tab);

    tab->setLayout(horizontalLayout);

    tab->layout()->addWidget(diceRoll);
    this->ui->tabWidget->addTab(tab, "Dice Roller");
}

void MainWindow::newDiceRollerWindow()
{
    QWidget *window = new QWidget(this, Qt::WindowFlags() | Qt::Window);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setWindowTitle("Dice Roller");

    DiceRollWidget *diceRoll = new DiceRollWidget(&dt, window);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(window);
    window->setLayout(horizontalLayout);

    window->layout()->addWidget(diceRoll);

    window->show();
}

void MainWindow::newDiceRollerDock()
{
    QDockWidget *dock = new QDockWidget(this);
    dock->setFloating(true);
    dock->setAttribute(Qt::WA_DeleteOnClose);
    dock->setWindowTitle("Dice Roller");

    DiceRollWidget *diceRoll = new DiceRollWidget(&dt, dock);
    dock->setWidget(diceRoll);

    dock->show();
}

void MainWindow::newFNGTab()
{
    QWidget *tab = new QWidget(this);
    FantasyNameGeneratorWidget *fng = new FantasyNameGeneratorWidget(tab);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(tab);

    tab->setLayout(horizontalLayout);

    tab->layout()->addWidget(fng);
    this->ui->tabWidget->addTab(tab, "Fantasy Name Generator");
}

void MainWindow::newFNGWindow()
{
    QWidget *window = new QWidget(this, Qt::WindowFlags() | Qt::Window);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setWindowTitle("Fantasy Name Generator");

    FantasyNameGeneratorWidget *fng = new FantasyNameGeneratorWidget(window);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(window);
    window->setLayout(horizontalLayout);

    window->layout()->addWidget(fng);

    window->show();
}

void MainWindow::newFNGDock()
{
    QDockWidget *dock = new QDockWidget(this);
    dock->setFloating(true);
    dock->setAttribute(Qt::WA_DeleteOnClose);
    dock->setWindowTitle("Fantasy Name Generator");

    FantasyNameGeneratorWidget *fng = new FantasyNameGeneratorWidget(dock);
    dock->setWidget(fng);

    dock->show();
}


void MainWindow::on_fantasyNameGenerator_clicked()
{
    this->newFNGTab();
}

