#ifndef FANTASYNAMEGENERATORITEM_H
#define FANTASYNAMEGENERATORITEM_H

#include <QMetaType>
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

Q_DECLARE_METATYPE(FantasyNameGeneratorItem*)

#endif // FANTASYNAMEGENERATORITEM_H
