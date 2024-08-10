#ifndef FNGGENERATEPAGEHTMLPARSER_H
#define FNGGENERATEPAGEHTMLPARSER_H

#include <QNetworkReply>
#include <QRegularExpression>
#include <QTreeWidgetItem>
#include <QString>

#include <vector>

#include <htmlparser/html.hpp>

#include "genders.h"

struct FNGGeneratorItem
{
    QString name;
    QString pageUrl;
    QStringList folders;

    Genders genders;
    QString scriptUrl;
    QString scriptName;

    QString err;
    QString testSignature;
    QTreeWidgetItem *errItem;

    bool large;
};

class FNGGeneratePageHTMLParser
{
public:
    FNGGeneratePageHTMLParser();

    void parse(const QString &body, FNGGeneratorItem& item);

private:
    html::parser p;
};

#endif // FNGGENERATEPAGEHTMLPARSER_H
