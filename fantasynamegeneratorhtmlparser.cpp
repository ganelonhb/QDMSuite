#include "fantasynamegeneratorhtmlparser.h"

FantasyNameGeneratorHtmlParser::FantasyNameGeneratorHtmlParser(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{}

void FantasyNameGeneratorHtmlParser::parse(QNetworkReply *r)
{
    html::node_ptr node = p.parse(r->readAll().toStdString());

    std::vector<html::node *> selected = node->select("ul.navmenu>li");

    QList<QTreeWidgetItem *> items;
    for (size_t i = 1; i < selected.size() - 4; ++i)
    {
        QString name = QString::fromStdString(selected[i]->to_text()).split('\n')[0].simplified();

        QTreeWidgetItem *item = new QTreeWidgetItem(0);
        item->setText(0, name);
        item->setCheckState(0, Qt::Unchecked);

        if (name == "Fantasy & Folklore")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/fantasynamegenerators/fantasy-and-folklore.svg"));
        if (name == "Real Names")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/fantasynamegenerators/real-names.svg"));
        if (name == "Places & Locations")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/fantasynamegenerators/places-and-locations.svg"));
        if (name == "Other Names")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/fantasynamegenerators/other-names.svg"));
        if (name == "Pop Culture")
            item->setIcon(0, QIcon(":/ui/icons/symbolic-dark/fantasynamegenerators/pop-culture.svg"));

        items.append(item);

        std::vector<html::node *> entries = selected[i]->select("ol.mainOl>li");
        std::vector<html::node *> subNav = selected[i]->select("ul.splitNavSct");
        bool hasSubNav = !subNav.empty();

        if (!hasSubNav)
        {
            for (html::node *entry : entries)
            {
                if (entry->get_attr("class") == "")
                {
                    QString entryName = QString::fromStdString(entry->to_text()).replace("/", " & ").simplified();
                    entryName = entryName.replace(" - New!", "").simplified();

                    QTreeWidgetItem *entryItem = new QTreeWidgetItem(0);
                    entryItem->setText(0, entryName);
                    entryItem->setCheckState(0, Qt::Unchecked);

                    std::vector<html::node *> a = entry->select("a");
                    QString linkName = QString::fromStdString("https://www.fantasynamegenerators.com/" + a[0]->get_attr("href"));

                    entryItem->setData(0, Qt::UserRole, name + ">" + entryName + "," + linkName);

                    item->addChild(entryItem);
                }
                else if (entry->get_attr("class") == "subList")
                {
                    QString subListName = QString::fromStdString(entry->to_text()).split('\n')[0].simplified();
                    subListName = subListName.replace(" - New!", "").replace(" >", "").replace("/", " & ").simplified();

                    QTreeWidgetItem* subListItem = new QTreeWidgetItem(0);
                    subListItem->setText(0, subListName);
                    subListItem->setCheckState(0, Qt::Unchecked);

                    item->addChild(subListItem);

                    std::vector<html::node *> subListItems = entry->select("ol.subNavOls>li");

                    for (html::node * subListNode : subListItems)
                    {
                        QString entryName = QString::fromStdString(subListNode->to_text()).replace("/", " & ").simplified();
                        entryName = entryName.replace(" - New!", "");

                        QTreeWidgetItem *entryItem = new QTreeWidgetItem(0);
                        entryItem->setText(0, entryName);
                        entryItem->setCheckState(0, Qt::Unchecked);

                        std::vector<html::node *> a = subListNode->select("a");
                        QString linkName = QString::fromStdString("https://www.fantasynamegenerators.com/" + a[0]->get_attr("href"));

                        entryItem->setData(0, Qt::UserRole, name + ">" + subListName + ">" + entryName + "," + linkName);

                        subListItem->addChild(entryItem);
                    }
                }
            }
        }
        else
        {
            for (html::node * entry : subNav)
            {
                std::string subNavName = entry->get_attr("id");
                if (subNavName == "rlSelect")
                {
                    std::vector<html::node *> lis = entry->select("li");

                    for (html::node * li : lis)
                    {
                        std::string rl = li->get_attr("class");

                        if (rl == "rlAll" || rl == "rlSelect") continue;

                        QString text = QString::fromStdString(li->to_text()).split('\n')[0].simplified();

                        std::vector<html::node *> rlOrigins = selected[i]->select("ul#" + rl + ">ol.mainOl>li");
                        QTreeWidgetItem* subNavTreeItem = new QTreeWidgetItem(0);
                        subNavTreeItem->setText(0, text);
                        subNavTreeItem->setCheckState(0, Qt::Unchecked);
                        item->addChild(subNavTreeItem);

                        for (html::node * subEntry : rlOrigins)
                        {
                            if (subEntry->get_attr("class") == "")
                            {
                                QString entryName = QString::fromStdString(subEntry->to_text()).replace("/", " & ").simplified();
                                entryName = entryName.replace(" - New!", "").simplified();

                                QTreeWidgetItem *entryItem = new QTreeWidgetItem(0);
                                entryItem->setText(0, entryName);
                                entryItem->setCheckState(0, Qt::Unchecked);

                                std::vector<html::node *> a = subEntry->select("a");
                                QString linkName = QString::fromStdString("https://www.fantasynamegenerators.com/" + a[0]->get_attr("href"));

                                entryItem->setData(0, Qt::UserRole, name + ">" + QString::fromStdString(subNavName) + ">" + entryName + "," + linkName);

                                subNavTreeItem->addChild(entryItem);
                            }
                            else if (subEntry->get_attr("class") == "subList")
                            {
                                QString subListName = QString::fromStdString(subEntry->to_text()).split('\n')[0].replace("/", " & ").simplified();
                                subListName = subListName.replace(" - New!", "").replace(" >", "").simplified();

                                QTreeWidgetItem* subListItem = new QTreeWidgetItem(0);
                                subListItem->setText(0, subListName);
                                subListItem->setCheckState(0, Qt::Unchecked);

                                subNavTreeItem->addChild(subListItem);

                                std::vector<html::node *> subListItems = subEntry->select("ol.subListed>li");

                                for (html::node * subListNode : subListItems)
                                {
                                    QString entryName = QString::fromStdString(subListNode->to_text()).replace("/", " & ").simplified();
                                    entryName = entryName.replace(" - New!", "");

                                    QTreeWidgetItem *entryItem = new QTreeWidgetItem(0);
                                    entryItem->setText(0, entryName);
                                    entryItem->setCheckState(0, Qt::Unchecked);

                                    std::vector<html::node *> a = subListNode->select("a");
                                    QString linkName = QString::fromStdString("https://www.fantasynamegenerators.com/" + a[0]->get_attr("href"));

                                    entryItem->setData(0, Qt::UserRole, name + ">" + QString::fromStdString(subNavName) + ">" + subListName + ">" + entryName + "," + linkName);

                                    subListItem->addChild(entryItem);
                                }
                            }
                        }
                    }
                    break;
                }
            }

        }
    }

    this->treeWidget->insertTopLevelItems(0, items);
}

void FantasyNameGeneratorHtmlParser::operator()(QNetworkReply *r)
{
    this->parse(r);
}
