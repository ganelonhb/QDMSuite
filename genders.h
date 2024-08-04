#ifndef GENDERS_H
#define GENDERS_H

#include <QMap>
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

#endif // GENDERS_H
