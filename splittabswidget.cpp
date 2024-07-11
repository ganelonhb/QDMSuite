#include "splittabswidget.h"

SplitTabsWidget::SplitTabsWidget(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *gridLayout = new QGridLayout(this);

    this->setLayout(gridLayout);
}

void SplitTabsWidget::createNewTab(SplitTabsWidget::TabSplitType split)
{
    if (!this->numWidgets)
    {
        ReportEmptyTabWidget *r = new ReportEmptyTabWidget(this);
        this->selected = r;
        QGridLayout *grid = new QGridLayout(r);
        r->setLayout(grid);

        WelcomeWidget *w = new WelcomeWidget(r);
        r->layout()->addWidget(w);


        this->layout()->addWidget(r);

        // connect a lambda?
        // connect(w, &QTabWidget::tabCloseRequested, this, []{});
    }
}

void SplitTabsWidget::tabEmpty(QWidget *widget)
{
    if (widget != nullptr)
    {
        this->layout()->removeWidget(widget);
        widget->deleteLater();
        --this->numWidgets;
    }

    if (!this->numWidgets)
    {

    }
}
