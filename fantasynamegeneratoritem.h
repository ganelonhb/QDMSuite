#ifndef FANTASYNAMEGENERATORITEM_H
#define FANTASYNAMEGENERATORITEM_H

#include <QString>
#include <cstdint>

#include "genderflags.h"

struct FantasyNameGeneratorItem
{
private:
    using gender_t = FantasyNameGender::namegenderflags_t;

public:
    FantasyNameGeneratorItem(QString name, QString scriptUrl, QString homeUrl, gender_t gender);
    FantasyNameGeneratorItem(QString name, QString scriptUrl, QString homeUrl, int gender);

    QString name;
    QString scriptUrl;
    QString homeUrl;

    gender_t gender;
};

#endif // FANTASYNAMEGENERATORITEM_H
