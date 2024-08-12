#ifndef GENDERS_H
#define GENDERS_H

#include <QMap>
#include <QList>
#include <QString>

class Genders
{
public:
    Genders();

    void insert(const QString &index, const QString &str);
    void insert(int index, const QString& str);

    QString operator[](QString idx);
    QString operator[](int idx);
    QString operator[]();

    QMap<QString, QString> &getMap();

private:
    QMap<QString, QString> m;
};

class Choices

{
public:
    Choices();

    void insert(const QString &str);

    QList<QString> &getList();

private:
    QList<QString> l;
};

#endif // GENDERS_H
