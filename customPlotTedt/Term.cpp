#include "Term.h"

Term::Term()
{

}

int Term::get_variable_count()
{
    return Term::variable_and_exponent.size();
}

bool Term::isEmpty()
{
    if (isEqualSign == false && isOperator == false && isBrace == false && isConstant == false)
        if (variable_and_exponent.size() == 0)
            return true;

    return false;
}
