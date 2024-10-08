#include "fantasynamegeneratordownloadwidget.h"
#include "helper_functions.hpp"
#include "ui_fantasynamegeneratordownloadwidget.h"

#include <iostream>

FantasyNameGeneratorDownloadWidget::FantasyNameGeneratorDownloadWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , ui(new Ui::FantasyNameGeneratorDownloadWidget)
{
    ui->setupUi(this);

    parseHtml = new FantasyNameGeneratorHtmlParser(this->ui->treeWidget);

    this->ui->downloadWidget->setVisible(false);

    nw = new QNetworkAccessManager(this);

    connect(nw, &QNetworkAccessManager::finished, this, &FantasyNameGeneratorDownloadWidget::finished);
    connect(this, &FantasyNameGeneratorDownloadWidget::closeRequested, this, &FantasyNameGeneratorDownloadWidget::onCloseRequested);
    connect(this, &FantasyNameGeneratorDownloadWidget::shown, this, &FantasyNameGeneratorDownloadWidget::onShow);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &FantasyNameGeneratorDownloadWidget::filterTreeItems);
}

FantasyNameGeneratorDownloadWidget::~FantasyNameGeneratorDownloadWidget()
{
    delete ui;
    delete parseHtml;

    if (activeReplies.length() > 0)
    {
        foreach(QNetworkReply * reply, activeReplies)
        {
            if (reply) reply->deleteLater();
        }
    }
}

void FantasyNameGeneratorDownloadWidget::download()
{
    nw->get(QNetworkRequest(QUrl("https://www.fantasynamegenerators.com/")));
}

void FantasyNameGeneratorDownloadWidget::finished(QNetworkReply *r)
{
    emit unblockClose();
    this->ui->treeWidget->blockSignals(true);
    if (r->error() != QNetworkReply::NoError) {
        emit downloadComplete(false);
        r->deleteLater();
        return;
    }

    parseHtml->parse(r);
    r->deleteLater();

    this->ui->treeWidget->blockSignals(false);
    emit downloadComplete(true);
}

void FantasyNameGeneratorDownloadWidget::on_cancelButton_clicked()
{
    ui->downloadWidget->setVisible(false);
    ui->downloadAllButton->setEnabled(true);
    ui->downloadSelectedButton->setEnabled(true);

    cancelRequest = 1;

    emit unblockClose();

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
inline void FantasyNameGeneratorDownloadWidget::iterateTreeCheck(QTreeWidgetItem* item, bool &allChecked)
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

inline FantasyNameGeneratorDownloadWidget::QTreeWidgetItemPtrList FantasyNameGeneratorDownloadWidget::items(QTreeWidget *widget, bool onlyChecked)
{
    QTreeWidgetItemPtrList p;

    for (int i = 0; i < widget->topLevelItemCount(); ++i)
        addTreeWidgetItemsToList(widget->topLevelItem(i), p, onlyChecked);

    return p;
}

inline void FantasyNameGeneratorDownloadWidget::addTreeWidgetItemsToList(QTreeWidgetItem * item, FantasyNameGeneratorDownloadWidget::QTreeWidgetItemPtrList &items, bool onlyChecked)
{
    if (!item) return;

    if (!onlyChecked || (onlyChecked && item->checkState(0) == Qt::Checked))
        items.append(item);

    if (!item->childCount()) return;


    for (int i = 0; i < item->childCount(); ++i)
        addTreeWidgetItemsToList(item->child(i), items, onlyChecked);
}

void FantasyNameGeneratorDownloadWidget::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    this->ui->treeWidget->blockSignals(true);
    setAllChildCheckStates(item, item->checkState(column));
    this->ui->treeWidget->blockSignals(false);
}

inline QList<FNGGeneratorItem> FantasyNameGeneratorDownloadWidget::downloadItems(QList<QTreeWidgetItem *> items)
{
    emit blockClose();
    QList<FNGGeneratorItem> fngItems;
    QList<FNGGeneratorItem> fails;

    foreach(QTreeWidgetItem *item , items)
    {
        if (!item->data(0, Qt::UserRole).isValid())
            continue;

        FNGGeneratorItem g;
        QStringList urlSplit = item->data(0, Qt::UserRole).toString().split(",");

        g.pageUrl = urlSplit[1];

        g.folders = urlSplit[0].split('>');

        g.name = g.folders.last();

        g.errItem = item;

        fngItems.push_back(g);
    }

    if (fngItems.empty()) return fails;

    ui->downloadProgressBar->setMaximum(fngItems.size());
    ui->downloadProgressBar->setValue(0);
    ui->downloadWidget->setVisible(true);
    ui->downloadAllButton->setEnabled(false);
    ui->downloadSelectedButton->setEnabled(false);

    foreach(FNGGeneratorItem item , fngItems)
    {
        if (cancelRequest > 0)
        {
            cancelRequest = 0;
            emit unblockClose();
            return fails;
        }

        QNetworkAccessManager m(this);
        QNetworkRequest request(QUrl(item.pageUrl));
        QNetworkReply * reply = m.get(request);
        activeReplies.push_back(reply);

        if (cancelRequest > 0)
        {
            cancelRequest = 0;
            emit unblockClose();
            return fails;
        }

        QEventLoop pauseUntilPageReplies;
        connect(reply, &QNetworkReply::finished, &pauseUntilPageReplies, &QEventLoop::quit);
        pauseUntilPageReplies.exec();

        QString response;
        if (reply->error() == QNetworkReply::NoError)
        {
            response = reply->readAll();
        }
        else
        {
            item.err = "network error";
            fails.append(item);
            ui->downloadProgressBar->setValue(ui->downloadProgressBar->value() + 1);
            continue;
        }

        reply->deleteLater();
        activeReplies.pop_back();

        if (cancelRequest > 0)
        {
            cancelRequest = 0;
            emit unblockClose();
            return fails;
        }

        FNGGeneratePageHTMLParser p;
        p.parse(response, item);

        QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

        QDir appDataDir(appDataPath);

        if (!appDataDir.exists())
            appDataDir.mkpath(".");

        QString fngPath = appDataPath + QDir::separator() + "fng";

        QDir fngDir(fngPath);

        if (!fngDir.exists())
            fngDir.mkpath(".");

        item.folders.removeAll("rlSelect");

        QString thisItemPath = fngPath + QDir::separator() + item.folders.join(QDir::separator());

        QDir thisItemDir(thisItemPath);
        if (!thisItemDir.exists())
            thisItemDir.mkpath(".");

        if (cancelRequest > 0)
        {
            cancelRequest = 0;
            emit unblockClose();
            return fails;
        }

        QNetworkRequest requestScript(QUrl(item.scriptUrl));
        QNetworkReply * replyScript = m.get(requestScript);
        activeReplies.push_back(replyScript);

        QEventLoop pauseUntilScriptReplies;
        connect(replyScript, &QNetworkReply::finished, &pauseUntilScriptReplies, &QEventLoop::quit);
        pauseUntilScriptReplies.exec();

        QString responseScript;
        if (replyScript->error() == QNetworkReply::NoError)
        {
            responseScript = replyScript->readAll();
        }
        else
        {
            ui->downloadProgressBar->setValue(ui->downloadProgressBar->value() + 1);
            item.err = "network error";
            fails.append(item);
            continue;
        }

        replyScript->deleteLater();
        activeReplies.pop_back();

        QFile scriptFile(thisItemPath + QDir::separator() + item.scriptName.replace(".js", ".qs"));
        if (!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->downloadProgressBar->setValue(ui->downloadProgressBar->value() + 1);
            item.err = "could not open " + thisItemPath + QDir::separator() + item.scriptName + ", " + scriptFile.errorString();
            fails.append(item);
            continue;
        }

        QRegularExpression reNames(R"(\bnames\b)");
        QRegularExpression renMs(R"(\bnMs\b)");
        QRegularExpression renm(R"(\bnm\b(?![\d"])");
        QRegularExpression reName(R"(\bname\b)");
        QRegularExpressionMatch matchNames = reNames.match(responseScript);
        QRegularExpressionMatch matchnMs = renMs.match(responseScript);
        QRegularExpressionMatch matchnm = renm.match(responseScript);
        QRegularExpressionMatch matchName = reName.match(responseScript);

        QString returnNames;

        if (matchNames.hasMatch())
            returnNames = "names";
        else if (matchName.hasMatch())
            returnNames = "name";
        else if (matchnm.hasMatch())
            returnNames = "nm";
        else if (matchnMs.hasMatch())
            returnNames = "nMs";

        QTextStream scriptOut(&scriptFile);
        scriptOut.setEncoding(QStringConverter::Utf8);
        scriptOut.setGenerateByteOrderMark(false);
        scriptOut << minifyJS(responseScript).replace("\n", "")
                         .replace(R"(document.getElementById("placeholder").appendChild(element);)", "return " + returnNames + ";")
                         .replace(R"(if(document.getElementById("result")){document.getElementById("placeholder").removeChild(document.getElementById("result"));})", "")
                         .replace(R"(element.appendChild(br);)", "")
                         .replace(R"(element.appendChild(document.createTextNode()" + returnNames + R"());)", "")
                         .replace(R"(br=document.createElement('br');)", "")
                         .replace(R"(element.setAttribute("id","result");)", "")
                         .replace(R"(var element=document.createElement("div");)", "")
                         .replace(R"(var br="";)", "")
                         .replace(R"(var br=[];)", "")
                         .replace(R"(br[i]=document.createElement('br');)", "")
                         .replace(R"(element.appendChild(br[i]);)", "")
                         .replace(R"(var choice=$("#radioChoice input[type='radio']:checked").val();)", "")
                         .replace(R"(element.appendChild(document.createTextNode(nm));)", "")
                         .replace(R"(element.appendChild(document.createTextNode(nMs));)", "")
                         .replace(R"(element.appendChild(document.createTextNode(name));)", "")
                         .replace(R"($('#firChange').is(':checked'))", "false")
                         .replace(R"($('#secChange').is(':checked'))", "false")
                         .replace(R"($("#firChange").val())", "false")
                         .replace(R"(element.appendChild(br[0]);)", "")
                         .replace(R"(br2=document.createElement('br');)", "")
                         .replace(R"(element.appendChild(document.createTextNode(names[i]));)", "")
                         .replace(R"(element.appendChild(document.createTextNode(names));)", "")
                         .replace(R"(br[0]=document.createElement('br');)", "")
                         .replace(R"(var element=document.createElement("div");)", "")
                         .replace(QRegularExpression(R"(\$\('#.+?'\)\.css\('.+?'\,'.+?'\);)"), "")
                         .replace(QRegularExpression(R"(testSwear\(.*?\);)"), "")
                         .replace(QRegularExpression(R"(testSwear\(.*?\);)"), "")
                         .replace(QRegularExpression(R"(console.log\(.*?\);)"), "")
                         .replace(QRegularExpression(R"(var\s+([a-zA-Z_]\w*)=document\.createElement\(\s*(['"][^'"]+['"])\s*\);)"), "")
                         .replace(QRegularExpression(R"(element\.setAttribute\(\s*(['"][^'"]+['"])\s*\);)"), "")
                         .replace(QRegularExpression(R"(element\.appendChild\(\s*([a-zA-Z_]\w*)\s*\);)"), "")
                         .replace(QRegularExpression(R"(element\.appendChild\(document\.createTextNode\(\s*([a-zA-Z_]\w*)\s*\)\);)"), "");


        scriptFile.close();

        QFile metaDataFile(thisItemPath + QDir::separator() + "meta.qoml");
        if (!metaDataFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->downloadProgressBar->setValue(ui->downloadProgressBar->value() + 1);
            item.err = "could not open " + thisItemPath + QDir::separator() + "meta.qoml" + ", " + scriptFile.errorString();
            fails.append(item);
            continue;
        }

        QTextStream metaOut(&metaDataFile);

        // meoooow

        metaOut << "name = \"" << item.name << "\"\n"
                << "script = \"" << item.scriptName << "\"\n"
                << "src = \"" << item.pageUrl << "\"\n"
                << "entrypoint = \"nameGen\"\n"
                << "large = " + QString(item.large ? "true" : "false") << '\n'
                << "choices = [";
        QList<QString> &list = item.choices.getList();

        foreach(QString str, list)
            metaOut << '"' << str << "\", ";

        metaOut << "]\n[genders]\n";

        QMap<QString, QString> &map = item.genders.getMap();

        foreach(QString str, map.keys())
        {
            std::cout << str.toStdString() << "=" << map[str].toStdString() << "\n";
            metaOut << '"' << str << "\" = \"" << map[str] << "\"\n";
        }



        metaDataFile.close();

        if (cancelRequest > 0)
        {
            cancelRequest = 0;
            emit unblockClose();
            return fails;
        }

        ui->downloadProgressBar->setValue(ui->downloadProgressBar->value() + 1);

        if (cancelRequest > 0)
        {
            cancelRequest = 0;
            emit unblockClose();
            return fails;
        }
    }

    ui->downloadWidget->setVisible(false);
    ui->downloadAllButton->setEnabled(true);
    ui->downloadSelectedButton->setEnabled(true);

    emit unblockClose();

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir appDataDir(appDataPath);

    if (!appDataDir.exists())
        appDataDir.mkpath(".");

    QString fngPath = appDataPath + QDir::separator() + "fng";

    QDir fngDir(fngPath);

    if (!fngDir.exists())
        fngDir.mkpath(".");

    emit dlItemsCompleteUpdateFileSystem(fngDir.absolutePath());
    return fails;
}

void FantasyNameGeneratorDownloadWidget::on_downloadSelectedButton_clicked()
{
    QList<FNGGeneratorItem> fails = downloadItems(items(ui->treeWidget, true));

    if (fails.size())
    {
        QList<QTreeWidgetItem *> selected = DownloadMessageBox::dlfailed(fails, this);

        while (selected.size())
        {
            QList<FNGGeneratorItem> failedRedownload = downloadItems(selected);

            selected = DownloadMessageBox::dlfailed(failedRedownload, this);
        }
    }
}


void FantasyNameGeneratorDownloadWidget::on_downloadAllButton_clicked()
{
    downloadItems(items(ui->treeWidget));
}

void FantasyNameGeneratorDownloadWidget::closeEvent(QCloseEvent *event)
{
    emit closeRequested();
    emit unblockClose();
    QWidget::closeEvent(event);
}

void FantasyNameGeneratorDownloadWidget::showEvent(QShowEvent *event)
{
    emit shown();
    QWidget::showEvent(event);
}

void FantasyNameGeneratorDownloadWidget::onCloseRequested()
{
    ui->downloadWidget->setVisible(false);
    ui->downloadAllButton->setEnabled(true);
    ui->downloadSelectedButton->setEnabled(true);

    cancelRequest = 1;
}

void FantasyNameGeneratorDownloadWidget::onShow()
{
    cancelRequest = 0;
}

void FantasyNameGeneratorDownloadWidget::filterTreeItems(const QString &text)
{
    QTreeWidgetItemIterator it(ui->treeWidget);

    while (*it)
    {
        QTreeWidgetItem *item = *it;

        bool match = item->text(0).contains(text, Qt::CaseInsensitive);
        item->setHidden(!match);

        if (match)
        {
            QTreeWidgetItem *parent = item->parent();
            while (parent)
            {
                parent->setHidden(false);
                ui->treeWidget->expandItem(parent);
                parent = parent->parent();
            }
        }

        ++it;
    }
}
