#ifndef FNGGENERATEPAGEHTMLPARSER_H
#define FNGGENERATEPAGEHTMLPARSER_H

#include <QNetworkReply>
#include <QString>

#include <vector>

#include <htmlparser/html.hpp>

#include "genders.h"

struct FNGGeneratorItem
{
    QString name;
    QString pageUrl;
    QStringList folders;
};

class FNGGeneratePageHTMLParser
{
public:
    FNGGeneratePageHTMLParser();

    void parse(const QString &body);

private:
    html::parser p;
};

#endif // FNGGENERATEPAGEHTMLPARSER_H
