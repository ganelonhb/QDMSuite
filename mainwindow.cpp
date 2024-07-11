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
    this->newWidget(new DiceRollWidget(&dt), WidgetType::FLOATING_DOCK, "Dice Roller");
}

void MainWindow::newDiceRollerTab()
{
    this->newWidget(new DiceRollWidget(&dt), WidgetType::TAB, "Dice Roller");
}

void MainWindow::newDiceRollerWindow()
{
    this->newWidget(new DiceRollWidget(&dt), WidgetType::WINDOW, "Dice Roller");
}

void MainWindow::newDiceRollerDock()
{
    this->newWidget(new DiceRollWidget(&dt), WidgetType::FLOATING_DOCK, "Dice Roller");
}

void MainWindow::newFNGTab()
{
    this->newWidget(new FantasyNameGeneratorWidget, WidgetType::TAB, "Fantasy Name Generator");
}

void MainWindow::newFNGWindow()
{
    this->newWidget(new FantasyNameGeneratorWidget, WidgetType::WINDOW, "Fantasy Name Generator");
}

void MainWindow::newFNGDock()
{
    this->newWidget(new FantasyNameGeneratorWidget, WidgetType::FLOATING_DOCK, "Fantasy Name Generator");
}


void MainWindow::on_fantasyNameGenerator_clicked()
{
    this->newWidget(new FantasyNameGeneratorWidget, WidgetType::TAB, "Fantasy Name Generator");
}

void MainWindow::newWidget(QWidget *widget, MainWindow::WidgetType wt, const QString &title)
{

    if (wt == MainWindow::WidgetType::WINDOW)
    {
        QWidget *window = new QWidget(this, Qt::WindowFlags() | Qt::Window);
        window->setAttribute(Qt::WA_DeleteOnClose);
        window->setWindowTitle(title);

        widget->setParent(window);
        QHBoxLayout* horizontalLayout = new QHBoxLayout(window);
        window->setLayout(horizontalLayout);

        window->layout()->addWidget(widget);

        window->show();
    }
    else if (wt == MainWindow::WidgetType::TAB)
    {
        QWidget *tab = new QWidget(this);
        widget->setParent(tab);
        QHBoxLayout* horizontalLayout = new QHBoxLayout(tab);

        tab->setLayout(horizontalLayout);

        tab->layout()->addWidget(widget);
        this->ui->tabWidget->addTab(tab, title);
        this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count() - 1);
    }
    else if (wt == MainWindow::WidgetType::FLOATING_DOCK)
    {
        QDockWidget *dock = new QDockWidget(this);
        dock->setFloating(true);
        dock->setAttribute(Qt::WA_DeleteOnClose);
        dock->setWindowTitle(title);

        widget->setParent(dock);
        dock->setWidget(widget);

        dock->show();
    }

    return;
}

