#ifndef DICEROLL_H
#define DICEROLL_H

class DiceRoll
{
public:
    DiceRoll(int sides, int result);

    int sides() const;
    int result() const;

private:
    int _sides;
    int _result;
};

#endif // DICEROLL_H
