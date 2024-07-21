#ifndef EXPRTK_METHODS_H
#define EXPRTK_METHODS_H

#include <QRandomGenerator>
#include <QtTypes>
#include <exprtk/exprtk.hpp>

template <typename T>
struct random_int : exprtk::ifunction<T>
{
    random_int()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        return T(QRandomGenerator::global()->bounded(qint64(v1), qint64(v2)));
    }
};

template <typename T>
struct meemo_operation : exprtk::ifunction<T>
{
    meemo_operation()
        : exprtk::ifunction<T>(1)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1) override
    {
        Q_UNUSED(v1);

        return T(3223);
    }
};

#endif // EXPRTK_METHODS_H
