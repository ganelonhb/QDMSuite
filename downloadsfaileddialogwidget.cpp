#include "downloadsfaileddialogwidget.h"
#include "ui_downloadsfaileddialogwidget.h"

DownloadsFailedDialogWidget::DownloadsFailedDialogWidget(QList<FNGGeneratorItem> items, QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
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

QList<QTreeWidgetItem *> DownloadsFailedDialogWidget::getSelected()
{
    return selected;
}

void DownloadsFailedDialogWidget::on_dnrButton_clicked()
{
    selected.clear();
    close();
}


void DownloadsFailedDialogWidget::on_rButton_clicked()
{
    QList<QTreeWidgetItem *> results;

    foreach(QListWidgetItem * item, ui->failList->selectedItems())
        if (item->checkState() == Qt::Checked) results.push_back(treeItems[item->text()]);

    close();
}

void DownloadsFailedDialogWidget::closeEvent(QCloseEvent *event)
{
    emit dialogClosed();
    QWidget::closeEvent(event);
}
