#ifndef EXPRTKEXCEPTIONS_H
#define EXPRTKEXCEPTIONS_H

#include <QException>

class ExprTkDivByZeroException : public QException
{
public:
    ExprTkDivByZeroException() {}

    const char* what() const throw() override
    {
        return "Error: Could not divide by zero.";
    }
};

class ExprTkParseException : public QException
{
public:
    ExprTkParseException() {}

    const char* what() const throw() override
    {
        return "Error: Could not parse an expression.";
    }
};

class ExprTkImaginaryException : public QException
{
public:
    ExprTkImaginaryException() {}

    const char* what() const throw() override
    {
        return "Error: The result is imaginary and is not supported.";
    }
};

class ExprTkOverflowException : public QException
{
public:
    ExprTkOverflowException() {}

    const char* what() const throw() override
    {
        return "Error: The result will overflow a double, if you can believe it.";
    }
};

#endif // EXPRTKEXCEPTIONS_H
