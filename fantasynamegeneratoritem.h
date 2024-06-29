#ifndef FANTASYNAMEGENERATORITEM_H
#define FANTASYNAMEGENERATORITEM_H

#include <QString>

struct FantasyNameGeneratorItem
{
public:
    FantasyNameGeneratorItem(QString name, QString category, QString subCategory, QString url);

    QString name;
    QString category;
    QString subCategory;
    QString url;
};

#endif // FANTASYNAMEGENERATORITEM_H
