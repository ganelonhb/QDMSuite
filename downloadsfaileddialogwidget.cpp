#include "downloadsfaileddialogwidget.h"
#include "ui_downloadsfaileddialogwidget.h"

DownloadsFailedDialogWidget::DownloadsFailedDialogWidget(QList<FNGGeneratorItem> items, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadsFailedDialogWidget)
    , items(items)
{
    ui->setupUi(this);

    foreach(FNGGeneratorItem item, items)
    {
        QListWidgetItem *i = new QListWidgetItem(ui->failList);
        i->setText(item.name);
        i->setData(Qt::UserRole, item.err);
        i->setCheckState(Qt::Unchecked);
        treeItems.insert(item.name, item.errItem);

        ui->failList->addItem(i);
    }
}

DownloadsFailedDialogWidget::~DownloadsFailedDialogWidget()
{
    delete ui;
}

void DownloadsFailedDialogWidget::on_failList_itemSelectionChanged()
{
    QList<QListWidgetItem *> items = ui->failList->selectedItems();

    if (items.empty())
    {
        ui->infoText->setText("");
        return;
    }

    ui->infoText->setText(items[0]->data(Qt::UserRole).toString());
}

