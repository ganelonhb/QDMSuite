#ifndef SWEARCHECKER_H
#define SWEARCHECKER_H

#include <QList>
#include <QStringList>
#include <QByteArray>
#include <QRegularExpression>
#include <QMutex>
#include <QMutexLocker>

class SwearChecker
{
public:
    SwearChecker();

    QString swearCheck(const QString& name, const QString& replacement="") const;
    bool isClean(const QString& name) const;

    static const SwearChecker global();

private:
    static const QList<QByteArray> swears;
    static const SwearChecker _global;
};

#endif // SWEARCHECKER_H
