#ifndef EXPRTKPARSEEXCEPTION_H
#define EXPRTKPARSEEXCEPTION_H

#include <QException>

class ExprTkParseException : public QException
{
public:
    ExprTkParseException();

    const char* what() const throw() override;
};

#endif // EXPRTKPARSEEXCEPTION_H
