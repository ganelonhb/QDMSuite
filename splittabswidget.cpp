#include "splittabswidget.h"
#include <iostream>
#include "fantasynamegeneratorwidget.h"

SplitTabsWidget::SplitTabsWidget(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *gridLayout = new QGridLayout(this);

    this->setLayout(gridLayout);

    this->tabPressedEventFilter = new TabPressedEventFilter(this);

    connect(this->tabPressedEventFilter, &TabPressedEventFilter::tabClicked, this, &SplitTabsWidget::onTabClicked);
    DraggableTabWidget *r = new DraggableTabWidget(this);
    r->setTabsClosable(true);
    r->setMovable(true);
    this->_selected = r;
    QWidget *tab = new QWidget(r);
    QGridLayout *grid = new QGridLayout(tab);
    WelcomeWidget *w = new WelcomeWidget(tab);
    tab->setLayout(grid);
    tab->layout()->addWidget(w);
    r->addTab(tab, "Home");
    installEventFilterRecursively(r, tabPressedEventFilter);
    this->layout()->addWidget(r);

    auto tabRemovedLambda = [r, this](int index){
        if(qobject_cast<QDMSWidget *>(r->widget(index)->layout()->itemAt(0)->widget())->isCloseBlocked())
        {
            QMessageBox::warning(this, "Could not Remove Tab", "Cannot remove tab while a download is in progress\nYou can cancel the download, if you would like.");
            return;
        }

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
                QGridLayout *thisGrid = qobject_cast<QGridLayout *>(this->layout());
                int row, column, rowSpan, columnSpan;
                thisGrid->getItemPosition(thisGrid->indexOf(r), &row, &column, &rowSpan, &columnSpan);

                QPalette palette = this->selected()->palette();

                this->layout()->removeWidget(r);
                r->deleteLater();

                DraggableTabWidget *item = nullptr;

                bool resetPos = false;

                if (row == 0 && column == 0)
                {
                    if (this->mode == TabSplitMode::HORIZONTAL)
                        item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,1)->widget());
                    else
                        item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(1,0)->widget());

                    resetPos = true;
                }
                else
                {
                    item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,0)->widget());
                }

                if (resetPos)
                {
                    thisGrid->removeWidget(item);
                    thisGrid->addWidget(item, 0, 0);
                }


                item->setPalette(palette);
                this->_selected = item;
                this->mode = TabSplitMode::SINGLE;
                emit this->single();
            }
        }
    };

    auto dropRemoveLambda = [r, this]{
        if (r->count() == 0)
        {
            QGridLayout *thisGrid = qobject_cast<QGridLayout *>(this->layout());
            int row, column, rowSpan, columnSpan;
            thisGrid->getItemPosition(thisGrid->indexOf(r), &row, &column, &rowSpan, &columnSpan);

            QPalette palette = this->selected()->palette();

            this->layout()->removeWidget(r);
            r->deleteLater();

            DraggableTabWidget *item = nullptr;

            bool resetPos = false;

            if (row == 0 && column == 0)
            {
                if (this->mode == TabSplitMode::HORIZONTAL)
                    item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,1)->widget());
                else
                    item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(1,0)->widget());

                resetPos = true;
            }
            else
            {
                item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,0)->widget());
            }

            if (resetPos)
            {
                thisGrid->removeWidget(item);
                thisGrid->addWidget(item, 0, 0);
            }


            item->setPalette(palette);
            this->_selected = item;
            this->mode = TabSplitMode::SINGLE;
            emit this->single();
        }
    };

    auto dropAcceptedLambda = [r, this] {
        if (r != this->_selected)
        {
            QPalette palette = this->_selected->palette();
            QColor selectedTabColor = palette.color(QPalette::Highlight);
            int lum = qGray(selectedTabColor.red(), selectedTabColor.green(), selectedTabColor.blue());
            QColor gray = QColor(lum,lum,lum);
            QPalette newPalette = palette;
            newPalette.setColor(QPalette::Highlight, gray);
            this->selected()->setPalette(newPalette);
            r->setPalette(palette);
            this->_selected = r;
        }
    };

    connect(r, &DraggableTabWidget::tabCloseRequested, this, tabRemovedLambda);
    connect(r, &DraggableTabWidget::dropRemoveEvent, this, dropRemoveLambda);
    connect(r, &DraggableTabWidget::dropAccepted, this, dropAcceptedLambda);
}

void SplitTabsWidget::createNewTab(TabSplitType split)
{
    if (this->mode == TabSplitMode::SINGLE)
    {
        DraggableTabWidget *r = new DraggableTabWidget(this);
        r->setTabsClosable(true);
        r->setMovable(true);

        QPalette palette = this->selected()->palette();
        QColor selectedTabColor = palette.color(QPalette::Highlight);
        int lum = qGray(selectedTabColor.red(), selectedTabColor.green(), selectedTabColor.blue());
        QColor gray = QColor(lum,lum,lum);
        QPalette newPalette = palette;
        newPalette.setColor(QPalette::Highlight, gray);
        this->selected()->setPalette(newPalette);
        r->setPalette(palette);

        this->_selected = r;
        QWidget *tab = new QWidget(r);
        QGridLayout *grid = new QGridLayout(tab);
        WelcomeWidget *w = new WelcomeWidget(tab);
        tab->setLayout(grid);
        tab->layout()->addWidget(w);
        r->addTab(tab, "Home");
        installEventFilterRecursively(r, tabPressedEventFilter);

        if (QGridLayout *l = qobject_cast<QGridLayout *>(this->layout()); split == TabSplitType::HORIZONTAL)
        {
            l->addWidget(r, 0, 1);
        }
        else
        {
            l->addWidget(r, 1, 0);
        }

        this->mode = (split == TabSplitType::HORIZONTAL) ? TabSplitMode::HORIZONTAL : TabSplitMode::VERTICAL;

        auto tabRemovedLambda = [r, this](int index){
            if(qobject_cast<QDMSWidget *>(r->widget(index)->layout()->itemAt(0)->widget())->isCloseBlocked())
            {
                QMessageBox::warning(this, "Could not Remove Tab", "Cannot remove tab while a download is in progress\nYou can cancel the download, if you would like.");
                return;
            }

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
                    QGridLayout *thisGrid = qobject_cast<QGridLayout *>(this->layout());
                    int row, column, rowSpan, columnSpan;
                    thisGrid->getItemPosition(thisGrid->indexOf(r), &row, &column, &rowSpan, &columnSpan);

                    QPalette palette = this->selected()->palette();

                    this->layout()->removeWidget(r);
                    r->deleteLater();

                    DraggableTabWidget *item = nullptr;

                    bool resetPos = false;

                    if (row == 0 && column == 0)
                    {
                        if (this->mode == TabSplitMode::HORIZONTAL)
                            item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,1)->widget());
                        else
                            item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(1,0)->widget());

                        resetPos = true;
                    }
                    else
                    {
                        item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,0)->widget());
                    }

                    if (resetPos)
                    {
                        thisGrid->removeWidget(item);
                        thisGrid->addWidget(item, 0, 0);
                    }


                    item->setPalette(palette);
                    this->_selected = item;
                    this->mode = TabSplitMode::SINGLE;
                    emit this->single();
                }
            }
        };

        auto dropRemoveLambda = [r, this] {
            if (r->count() == 0)
            {
                QGridLayout *thisGrid = qobject_cast<QGridLayout *>(this->layout());
                int row, column, rowSpan, columnSpan;
                thisGrid->getItemPosition(thisGrid->indexOf(r), &row, &column, &rowSpan, &columnSpan);

                QPalette palette = this->selected()->palette();

                this->layout()->removeWidget(r);
                r->deleteLater();

                DraggableTabWidget *item = nullptr;

                bool resetPos = false;

                if (row == 0 && column == 0)
                {
                    if (this->mode == TabSplitMode::HORIZONTAL)
                        item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,1)->widget());
                    else
                        item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(1,0)->widget());

                    resetPos = true;
                }
                else
                {
                    item = qobject_cast<DraggableTabWidget *>(thisGrid->itemAtPosition(0,0)->widget());
                }

                if (resetPos)
                {
                    thisGrid->removeWidget(item);
                    thisGrid->addWidget(item, 0, 0);
                }


                item->setPalette(palette);
                this->_selected = item;
                this->mode = TabSplitMode::SINGLE;
                emit this->single();
            }
        };

        auto dropAcceptedLambda = [r, this] {
            if (r != this->_selected)
            {
                QPalette palette = this->_selected->palette();
                QColor selectedTabColor = palette.color(QPalette::Highlight);
                int lum = qGray(selectedTabColor.red(), selectedTabColor.green(), selectedTabColor.blue());
                QColor gray = QColor(lum,lum,lum);
                QPalette newPalette = palette;
                newPalette.setColor(QPalette::Highlight, gray);
                this->selected()->setPalette(newPalette);
                r->setPalette(palette);
                this->_selected = r;
            }
        };

        connect(r, &DraggableTabWidget::tabCloseRequested, this, tabRemovedLambda);
        connect(r, &DraggableTabWidget::dropRemoveEvent, this, dropRemoveLambda);
        connect(r, &DraggableTabWidget::dropAccepted, this, dropAcceptedLambda);
    }
}

DraggableTabWidget *SplitTabsWidget::selected()
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


void SplitTabsWidget::onTabClicked(DraggableTabWidget *tabWidget)
{
    if (tabWidget != this->_selected)
    {
        QPalette palette = this->_selected->palette();
        QColor selectedTabColor = palette.color(QPalette::Highlight);
        int lum = qGray(selectedTabColor.red(), selectedTabColor.green(), selectedTabColor.blue());
        QColor gray = QColor(lum,lum,lum);
        QPalette newPalette = palette;
        newPalette.setColor(QPalette::Highlight, gray);
        this->selected()->setPalette(newPalette);
        tabWidget->setPalette(palette);
        this->_selected = tabWidget;
    }
}

inline void SplitTabsWidget::installEventFilterRecursively(QWidget *widget, QObject *filter)
{
    widget->installEventFilter(filter);

    const QList<QWidget *> children = widget->findChildren<QWidget *>();

    if (!children.length()) return;

    foreach(QWidget *child, children)
    {
        installEventFilterRecursively(child, filter);
    }
}
