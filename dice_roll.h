#ifndef DICE_ROLL_H
#define DICE_ROLL_H

#include <QRandomGenerator>
#include <exprtk/exprtk.hpp>

#include "diceroll.h"
#include "dicerolltracker.h"

template <typename T>
struct dice_roll : exprtk::ifunction<T>
{
    dice_roll()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    DiceRollTracker* tracker = nullptr;

    inline T operator()(const T& v1, const T& v2) override
    {
        T sum = T(0);

        for (quint32 i = 0; i < quint32(v1); ++i) {
            T val = T(QRandomGenerator::global()->bounded(quint32(1), quint32(v2) + 1));
            if (tracker != nullptr) {
                DiceRoll d = DiceRoll(v2, val);
                tracker->append(d);
            }
            sum += val;
        }

        return sum;
    }
};

#endif // DICE_ROLL_H
