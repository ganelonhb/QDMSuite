#ifndef EXPRTK_METHODS_H
#define EXPRTK_METHODS_H

#include <QRandomGenerator>
#include <QtTypes>
#include <type_traits>
#include <exprtk/exprtk.hpp>

#include "exprtkexceptions.hpp"

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
        qint64 a = v1;
        qint64 b = v2;

        if (a > b) std::swap(a, b);

        return T(QRandomGenerator::global()->bounded(qint64(a), qint64(b)));
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

template <typename T>
struct gcd : exprtk::ifunction<T>
{
    gcd()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        T a = std::abs(v1);
        T b = std::abs(v2);

        if (a == T(0) && b == T(0))
            return 0;
        else if (a == 0)
            return b;
        else if (b == 0)
            return a;

        if (std::is_integral<T>::value)
        {
            while (b != 0)
            {
                T temp = b;
                b = static_cast<qint128>(a) % static_cast<qint128>(b);
                a = temp;
            }
        }
        else if (std::is_floating_point<T>::value)
        {
            const T tol = sizeof(T) >= 16 ? 1e-4500l : 1e-250;

            while (std::abs(b) > tol)
            {
                T temp = b;
                b = sizeof(T) >= 16 ? std::fmodl(a, b) : std::fmod(a, b);
                a = temp;
            }
        }

        return a;
    }
};

template <typename T>
struct lcm : exprtk::ifunction<T>
{
    lcm()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        if (v1 == 0 || v2 == 0)
            return 0;

        T gcdValue = GCD(v1, v2);

        if (gcdValue == 0)
            return 0;

        return std::abs(v1 * v2) / gcdValue;
    }

    gcd<T> GCD;
};

template <typename T>
struct xrt : exprtk::ifunction<T>
{
    xrt()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        if (v2 == 0)
            throw ExprTkDivByZeroException();

        return std::pow(v2, 1/v1);
    }
};

template <typename T>
struct factorial : exprtk::ifunction<T>
{
    factorial()
        : exprtk::ifunction<T>(1)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1) override
    {
        if (v1 < 0) throw ExprTkImaginaryException();

        //if (v1 > 170) throw ExprTkOverflowException();

        if (std::is_integral<T>::value)
        {
            if (v1 < 2)
                return 1;

            return v1 * (*this)(v1 - 1);
        }
        else if (std::is_floating_point<T>::value) {
            if (v1 > 1754 && sizeof(T) >= 16)
                throw ExprTkOverflowException();
            else if (v1 > 170 && sizeof(T) >= 8 && sizeof(T) < 16)
                throw ExprTkOverflowException();
            else if (v1 > 34 && sizeof(T) >= 4 && sizeof(T) < 8)
                throw ExprTkOverflowException();
            else if (v1 > 5 && sizeof(T) < 4)
                throw ExprTkOverflowException();

            return std::tgamma(v1 + 1);
        }
    }
};

#endif // EXPRTK_METHODS_H
