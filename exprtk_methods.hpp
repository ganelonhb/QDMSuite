#ifndef EXPRTK_METHODS_H
#define EXPRTK_METHODS_H

#include <QRandomGenerator>
#include <QtTypes>
#include <type_traits>
#include <exprtk/exprtk.hpp>

#include "exprtkexceptions.hpp"

template <typename T>
    requires std::floating_point<T>
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
    requires std::floating_point<T>
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
    requires std::floating_point<T>
struct gcd : exprtk::ifunction<T>
{
    gcd()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        if constexpr(std::is_same_v<T, long double>)
        {
            T a = std::fabsl(v1);
            T b = std::fabsl(v2);

            if (a == 0.L && b == 0.L)
                return 0.L;
            else if (a == 0.L)
                return b;
            else if (b == 0.L)
                return a;

            const T tol = 1e-18L;

            while (std::fabsl(b) > tol)
            {
                T temp = b;
                b = std::fmodl(a, b);
                a = temp;
            }

            return a;
        }
        else if constexpr(std::is_same_v<T, double>)
        {
            T a = std::fabs(v1);
            T b = std::fabs(v2);

            if (a == 0. && b == 0.)
                return 0.;
            else if (a == 0.)
                return b;
            else if (b == 0.)
                return a;

            const T tol = 1e-15;

            while (std::fabs(b) > tol)
            {
                T temp = b;
                b = std::fmod(a, b);
                a = temp;
            }

            return a;
        }
        else
        {
            T a = std::fabsf(v1);
            T b = std::fabsf(v2);

            if (a == 0.f && b == 0.f)
                return 0.f;
            else if (a == 0.f)
                return b;
            else if (b == 0.f)
                return a;

            const T tol = 1e-6;

            while (std::fabsf(b) > tol)
            {
                T temp = b;
                b = std::fmodf(a, b);
                a = temp;
            }

            return a;
        }
    }
};

template <typename T>
    requires std::floating_point<T>
struct lcm : exprtk::ifunction<T>
{
    lcm()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        if constexpr(std::is_same_v<T, long double>)
        {
            if (v1 == 0.L || v2 == 0.L)
                return 0.L;

            T gcdValue = GCD(v1, v2);

            if (gcdValue == 0.L)
                return 0.L;

            return std::fabsl(v1 * v2) / gcdValue;
        }
        else if constexpr(std::is_same_v<T, double>)
        {
            if (v1 == 0. || v2 == 0.)
                return 0.;

            T gcdValue = GCD(v1, v2);

            if (gcdValue == 0.)
                return 0.;

            return std::fabs(v1 * v2) / gcdValue;
        }
        else
        {
            if (v1 == 0.f || v2 == 0.f)
                return 0.f;

            T gcdValue = GCD(v1, v2);

            if (gcdValue == 0.f)
                return 0.f;

            return std::fabsf(v1 * v2) / gcdValue;
        }
    }

    gcd<T> GCD;
};

template <typename T>
    requires std::floating_point<T>
struct xrt : exprtk::ifunction<T>
{
    xrt()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1, const T& v2) override
    {
        if constexpr(std::is_same_v<T, long double>)
        {
            if (v1 == 0.L)
                throw ExprTkDivByZeroException();

            return std::powl(v2, 1.L / v1);
        }
        else if constexpr(std::is_same_v<T, double>)
        {
            if (v1 == 0.)
                throw ExprTkDivByZeroException();

            return std::pow(v2, 1.L / v1);
        }
        else
        {
            if (v1 == 0.f)
                throw ExprTkDivByZeroException();

            return pow(v2, 1.f / v1);
        }
    }
};

template <typename T>
    requires std::floating_point<T>
struct factorial : exprtk::ifunction<T>
{
    factorial()
        : exprtk::ifunction<T>(1)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& v1) override
    {

        if constexpr(std::is_same_v<T, long double>)
        {
            if (v1 < 0.L) throw ExprTkImaginaryException();

            if (v1 > 1754)
                throw ExprTkOverflowException();

            return std::tgammal(v1 + 1.L);
        }
        else if constexpr(std::is_same_v<T, double>)
        {
            if (v1 < 0.) throw ExprTkImaginaryException();
            if (v1 > 170)
                throw ExprTkOverflowException();

            return std::tgamma(v1 + 1.);
        }
        else
        {
            if (v1 < 0.f) throw ExprTkImaginaryException();
            if (v1 > 34)
                throw ExprTkOverflowException();

            return std::tgammaf(v1 + 1.f);
        }
    }
};

template <typename T>
    requires std::floating_point<T>
struct exprtk_atan2 : exprtk::ifunction<T>
{
    exprtk_atan2()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& y, const T& x) override
    {
        if constexpr(std::is_same_v<T, long double>)
            return std::atan2l(y, x);
        else if constexpr(std::is_same_v<T, double>)
            return std::atan2(y, x);
        else
            return std::atan2f(y, x);
    }
};

template <typename T>
    requires std::floating_point<T>
struct ln : exprtk::ifunction<T>
{
    ln()
        : exprtk::ifunction<T>(1)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& x) override
    {
        if constexpr(std::is_same_v<T, long double>)
            return std::logl(x);
        else if constexpr(std::is_same_v<T, double>)
            return std::log(x);
        else
            return std::logf(x);
    }
};

template <typename T>
    requires std::floating_point<T>
struct logb10 : exprtk::ifunction<T>
{
    logb10()
        : exprtk::ifunction<T>(1)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& x) override
    {
        if constexpr(std::is_same_v<T, long double>)
            return std::log10l(x);
        else if constexpr(std::is_same_v<T, double>)
            return std::log10(x);
        else
            return std::log10f(x);
    }
};

template <typename T>
    requires std::floating_point<T>
struct logx : exprtk::ifunction<T>
{
    logx()
        : exprtk::ifunction<T>(2)
    {
        exprtk::disable_has_side_effects(*this);
    }

    inline T operator()(const T& b, const T& x) override
    {        
        if constexpr(std::is_same_v<T, long double>)
            return std::log10l(x) / std::log10l(b);
        else if constexpr(std::is_same_v<T, double>)
            return std::log10(x) / std::log10(b);
        else
            return std::log10f(x) / std::log10f(b);
    }
};

#endif // EXPRTK_METHODS_H
