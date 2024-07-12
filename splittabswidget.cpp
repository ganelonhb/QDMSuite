#include "splittabswidget.h"

SplitTabsWidget::SplitTabsWidget(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *gridLayout = new QGridLayout(this);

    this->setLayout(gridLayout);

    QTabWidget *r = new QTabWidget(this);
    r->setTabsClosable(true);
    this->_selected = r;
    QWidget *tab = new QWidget(r);
    QGridLayout *grid = new QGridLayout(tab);
    WelcomeWidget *w = new WelcomeWidget(tab);
    tab->setLayout(grid);
    tab->layout()->addWidget(w);
    r->addTab(tab, "Home");

    this->layout()->addWidget(r);

    connect(r, &QTabWidget::tabCloseRequested, this, [r, this](int index){
        r->widget(index)->deleteLater();

        if (r->count() == 1) {
            if (this->mode == TabSplitMode::SINGLE)
            {
                this->_selected = r;
                QWidget *tab = new QWidget(this);
                QGridLayout *grid = new QGridLayout(r);
                WelcomeWidget *w = new WelcomeWidget();
                grid->addWidget(w);
                tab->setLayout(grid);
                tab->layout()->addWidget(w);
                r->addTab(tab, "Home");
            }
            else
            {
                this->layout()->removeWidget(r);
                r->deleteLater();
                QGridLayout *thisGrid = dynamic_cast<QGridLayout *>(this->layout());
                QLayoutItem *item = thisGrid->itemAt(0);
                this->_selected = dynamic_cast<QTabWidget *>(item->widget());
                this->mode = TabSplitMode::SINGLE;
                emit this->single();
            }
        }
    });
}

void SplitTabsWidget::createNewTab(TabSplitType split)
{
    if (this->mode == TabSplitMode::SINGLE)
    {
        QTabWidget *r = new QTabWidget(this);
        r->setTabsClosable(true);
        this->_selected = r;
        QWidget *tab = new QWidget(r);
        QGridLayout *grid = new QGridLayout(tab);
        WelcomeWidget *w = new WelcomeWidget(tab);
        tab->setLayout(grid);
        tab->layout()->addWidget(w);
        r->addTab(tab, "Home");

        // determine where to add and set mode
        //this->layout()->addWidget(r);
        if (QGridLayout *l = dynamic_cast<QGridLayout *>(this->layout()); split == TabSplitType::HORIZONTAL)
        {
            l->addWidget(r, 0, 1);
        }
        else
        {
            l->addWidget(r, 1, 0);
        }

        this->mode = (split == TabSplitType::HORIZONTAL) ? TabSplitMode::HORIZONTAL : TabSplitMode::VERTICAL;

        connect(r, &QTabWidget::tabCloseRequested, this, [r, this](int index){
            r->widget(index)->deleteLater();

            if (r->count() == 1) {
                if (this->mode == TabSplitMode::SINGLE)
                {
                    this->_selected = r;
                    QWidget *tab = new QWidget(this);
                    QGridLayout *grid = new QGridLayout(r);
                    WelcomeWidget *w = new WelcomeWidget();
                    grid->addWidget(w);
                    tab->setLayout(grid);
                    tab->layout()->addWidget(w);
                    r->addTab(tab, "Home");
                }
                else
                {
                    this->layout()->removeWidget(r);
                    r->deleteLater();
                    QGridLayout *thisGrid = dynamic_cast<QGridLayout *>(this->layout());
                    this->_selected = dynamic_cast<QTabWidget *>(thisGrid->itemAt(0)->widget());
                    this->mode = TabSplitMode::SINGLE;
                    emit this->single();
                }
            }
        });
    }
}

QTabWidget *SplitTabsWidget::selected()
{
    return this->_selected;
}

void SplitTabsWidget::createHorizontalTab()
{
    this->createNewTab(TabSplitType::HORIZONTAL);
}

void SplitTabsWidget::createVerticalTab()
{
    this->createNewTab(TabSplitType::VERTICAL);
}
