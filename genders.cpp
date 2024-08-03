#include "genders.h"

Genders::Genders() {}

void Genders::insert(const QString &index, const QString &str)
{
    QString i = index;

    if (i == "" || i == "namesMale")
        i = "void";
    else if (i == "namesFemale")
    {
        i = "1";
    }
    else if (i == "namesNeutral")
    {
        i = "2";
    }

    m.insert(index, str);
}

void Genders::insert(int index, const QString& str)
{
    m.insert(QString::number(index), str);
}

QString Genders::operator[](QString idx)
{
    return m[idx];
}

QString Genders::operator[](int idx)
{
    return m[QString::number(idx)];
}

QString Genders::operator[]()
{
    return m["void"];
}
