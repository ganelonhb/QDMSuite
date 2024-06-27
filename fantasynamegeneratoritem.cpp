#include "fantasynamegeneratoritem.h"

FantasyNameGeneratorItem::FantasyNameGeneratorItem(QString name, QString scriptUrl, QString homeUrl, gender_t gender)
    : name(name)
    , scriptUrl(scriptUrl)
    , homeUrl(homeUrl)
    , gender(gender)
{}


FantasyNameGeneratorItem::FantasyNameGeneratorItem(QString name, QString scriptUrl, QString homeUrl, int gender)
    : name(name)
    , scriptUrl(scriptUrl)
    , homeUrl(homeUrl)
    , gender(static_cast<uint8_t>(gender))
{}
