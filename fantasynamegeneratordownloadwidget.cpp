#include "fantasynamegeneratordownloadwidget.h"
#include "ui_fantasynamegeneratordownloadwidget.h"

FantasyNameGeneratorDownloadWidget::FantasyNameGeneratorDownloadWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , ui(new Ui::FantasyNameGeneratorDownloadWidget)
{
    ui->setupUi(this);

    parseHtml = new FantasyNameGeneratorHtmlParser(this->ui->treeWidget);

    this->ui->downloadWidget->setVisible(false);

    nw = new QNetworkAccessManager(this);

    connect(nw, &QNetworkAccessManager::finished, this, &FantasyNameGeneratorDownloadWidget::finished);

}

FantasyNameGeneratorDownloadWidget::~FantasyNameGeneratorDownloadWidget()
{
    delete ui;
    delete parseHtml;
}

void FantasyNameGeneratorDownloadWidget::download()
{
    nw->get(QNetworkRequest(QUrl("https://www.fantasynamegenerators.com/")));
}

void FantasyNameGeneratorDownloadWidget::finished(QNetworkReply *r)
{
    this->ui->treeWidget->blockSignals(true);
    if (r->error() != QNetworkReply::NoError) {
        emit downloadComplete(false);
        r->deleteLater();
        return;
    }

    parseHtml->parse(r);

    /* parse DOM and put in tree */
    r->deleteLater();

    this->ui->treeWidget->blockSignals(false);
    emit downloadComplete(true);
}

void FantasyNameGeneratorDownloadWidget::on_cancelButton_clicked()
{
    this->close();
}

void FantasyNameGeneratorDownloadWidget::on_unCheckAll_checkStateChanged(const Qt::CheckState &state)
{
    Q_UNUSED(state);

    this->ui->treeWidget->blockSignals(true);

    this->ui->checkAllCheckBox->blockSignals(true);
    this->ui->checkAllCheckBox->setCheckState(Qt::Unchecked);
    this->ui->checkAllCheckBox->blockSignals(false);

    this->ui->checkSelectedCheckBox->blockSignals(true);
    this->ui->checkSelectedCheckBox->setCheckState(Qt::Unchecked);
    this->ui->checkSelectedCheckBox->blockSignals(false);

    setAllCheckStates(this->ui->treeWidget, Qt::Unchecked);

    this->ui->unCheckAll->blockSignals(true);
    this->ui->unCheckAll->setCheckState(Qt::Unchecked);
    this->ui->unCheckAll->blockSignals(false);

    this->ui->treeWidget->blockSignals(false);
}

inline void FantasyNameGeneratorDownloadWidget::iterateTreeItems(QTreeWidgetItem* item, Qt::CheckState state)
{
    if (!item) return;

    item->setCheckState(0, state);

    for (int i = 0; i < item->childCount(); ++i)
        iterateTreeItems(item->child(i), state);
}

inline void FantasyNameGeneratorDownloadWidget::setAllCheckStates(QTreeWidget* widget, Qt::CheckState state)
{
    for (int i = 0; i < widget->topLevelItemCount(); ++i)
        iterateTreeItems(widget->topLevelItem(i), state);
}


void FantasyNameGeneratorDownloadWidget::on_treeWidget_itemSelectionChanged()
{
    this->ui->checkSelectedCheckBox->blockSignals(true);
    this->ui->checkSelectedCheckBox->setCheckState(Qt::Unchecked);
    this->ui->checkSelectedCheckBox->blockSignals(false);
}


void FantasyNameGeneratorDownloadWidget::on_checkAllCheckBox_checkStateChanged(const Qt::CheckState &state)
{
    this->ui->treeWidget->blockSignals(true);
    if (!this->ui->treeWidget->selectedItems().empty())
    {
        this->ui->checkSelectedCheckBox->blockSignals(true);
        this->ui->checkSelectedCheckBox->setCheckState(state);
        this->ui->checkSelectedCheckBox->blockSignals(false);
    }

    setAllCheckStates(this->ui->treeWidget, state);
    this->ui->treeWidget->blockSignals(false);
}


void FantasyNameGeneratorDownloadWidget::on_checkSelectedCheckBox_checkStateChanged(const Qt::CheckState &state)
{
    //this->ui->treeWidget->blockSignals(true);
    foreach(QTreeWidgetItem* item, this->ui->treeWidget->selectedItems())
        item->setCheckState(0, state);

    if (allChecked(this->ui->treeWidget))
    {
        this->ui->checkAllCheckBox->blockSignals(true);
        this->ui->checkAllCheckBox->setCheckState(Qt::Checked);
        this->ui->checkAllCheckBox->blockSignals(false);
    }
}


void FantasyNameGeneratorDownloadWidget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    this->ui->treeWidget->blockSignals(true);

    if (item->checkState(0) == Qt::Unchecked)
    {
        this->ui->checkAllCheckBox->blockSignals(true);
        this->ui->checkAllCheckBox->setCheckState(Qt::Unchecked);
        this->ui->checkAllCheckBox->blockSignals(false);
    }

    if (allChecked(this->ui->treeWidget))
    {
        this->ui->checkAllCheckBox->blockSignals(true);
        this->ui->checkAllCheckBox->setCheckState(Qt::Checked);
        this->ui->checkAllCheckBox->blockSignals(false);
    }

    bool allSelected = true;

    foreach(QTreeWidgetItem* i, this->ui->treeWidget->selectedItems())
        if (i->checkState(0) != Qt::Checked) allSelected = false;

    if (allSelected)
    {
        this->ui->checkSelectedCheckBox->blockSignals(true);
        this->ui->checkSelectedCheckBox->setCheckState(Qt::Checked);
        this->ui->checkSelectedCheckBox->blockSignals(false);
    }
    else
    {
        this->ui->checkSelectedCheckBox->blockSignals(true);
        this->ui->checkSelectedCheckBox->setCheckState(Qt::Unchecked);
        this->ui->checkSelectedCheckBox->blockSignals(false);
    }

    this->ui->treeWidget->blockSignals(false);

}

inline bool FantasyNameGeneratorDownloadWidget::allChecked(QTreeWidget* widget)
{
    bool allChecked = true;

    for (int i = 0; i < widget->topLevelItemCount(); ++i)
        iterateTreeCheck(widget->topLevelItem(i), allChecked);

    return allChecked;
}
inline void FantasyNameGeneratorDownloadWidget::iterateTreeCheck(QTreeWidgetItem* item, bool& allChecked)
{
    if (!item || !allChecked) return;

    if (item->checkState(0) == Qt::Unchecked)
    {
        allChecked = false;
        return;
    }

    for (int i = 0; i < item->childCount(); ++i)
        iterateTreeCheck(item->child(i), allChecked);
}

inline void FantasyNameGeneratorDownloadWidget::setAllChildCheckStates(QTreeWidgetItem * item, Qt::CheckState state)
{

    iterateTreeItems(item, state);
}

void FantasyNameGeneratorDownloadWidget::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    this->ui->treeWidget->blockSignals(true);
    setAllChildCheckStates(item, item->checkState(column));
    this->ui->treeWidget->blockSignals(false);
}