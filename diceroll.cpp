#include "diceroll.h"

/*    DiceRoll(int sides, int result);

    int sides() const { return this->_sides; }
    int result() const { return this->_result; */

DiceRoll::DiceRoll(int sides, int result)
    : _sides(sides),
    _result(result)
{}

int DiceRoll::sides() const
{
    return this->_sides;
}

int DiceRoll::result() const
{
    return this->_result;
}
