#include "dicerolltracker.h"

DiceRollTracker::DiceRollTracker(QObject *parent)
    : QObject{parent}
{}

void DiceRollTracker::clear()
{
    this->_results.clear();

    emit this->changed(this->_results);
}


void DiceRollTracker::append(DiceRoll& value)
{
    this->_results.append(value);

    emit this->changed(this->_results);
}

void DiceRollTracker::append(const QList<DiceRoll>& other)
{
    this->_results.append(other);

    emit this->changed(this->_results);
}

QList<DiceRoll>::iterator DiceRollTracker::begin()
{
    return this->_results.begin();
}
QList<DiceRoll>::iterator DiceRollTracker::end()
{
    return this->_results.end();
}

QList<DiceRoll>::const_iterator DiceRollTracker::cbegin() const
{
    return this->_results.cbegin();
}

QList<DiceRoll>::const_iterator DiceRollTracker::cend() const
{
    return this->_results.cend();
}


const DiceRoll& DiceRollTracker::at(int i) const
{
    return this->_results.at(i);
}

int DiceRollTracker::size() const
{
    return this->_results.size();
}

void DiceRollTracker::removeAt(int i)
{
    this->_results.removeAt(i);

    emit this->changed(this->_results);
}

const DiceRoll& DiceRollTracker::operator[](int i) const
{
    return this->_results[i];
}

const DiceRoll& DiceRollTracker::first() const
{
    return this->_results.first();
}

const DiceRoll& DiceRollTracker::last() const
{
    return this->_results.last();
}

bool DiceRollTracker::empty() const
{
    return this->_results.empty();
}
