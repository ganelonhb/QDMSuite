#ifndef FANTASYNAMEGENERATORHTMLPARSER_H
#define FANTASYNAMEGENERATORHTMLPARSER_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QNetworkReply>

#include <vector>

#include <htmlparser/html.hpp>

class FantasyNameGeneratorHtmlParser
{
public:
    FantasyNameGeneratorHtmlParser(QTreeWidget *treeWidget);

    void parse(QNetworkReply *r);

    void operator()(QNetworkReply *r);

private:
    QTreeWidget *treeWidget;
    html::parser p;
};

#endif // FANTASYNAMEGENERATORHTMLPARSER_H
