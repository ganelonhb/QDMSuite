#ifndef DICEROLLTRACKER_H
#define DICEROLLTRACKER_H

#include <QObject>
#include <QList>

#include "diceroll.h"

class DiceRollTracker : public QObject
{
    Q_OBJECT
public:
    explicit DiceRollTracker(QObject *parent = nullptr);

    void clear();

    void append(DiceRoll& value);
    void append(const QList<DiceRoll>& other);

    QList<DiceRoll>::iterator begin();
    QList<DiceRoll>::iterator end();

    QList<DiceRoll>::const_iterator cbegin() const;
    QList<DiceRoll>::const_iterator cend() const;

    const DiceRoll& at(int i) const;

    int size() const;

    void removeAt(int i);

    const DiceRoll& operator[](int i) const;

    const DiceRoll& first() const;
    const DiceRoll& last() const;

    bool empty() const;

signals:
    void changed(const QList<DiceRoll>& results);


private:
    QList<DiceRoll> _results;
};

#endif // DICEROLLTRACKER_H
