#include "exprtkparseexception.h"

ExprTkParseException::ExprTkParseException() {}

const char* ExprTkParseException::what() const throw()
{
    return "Error: Could not parse an expression.";
}
