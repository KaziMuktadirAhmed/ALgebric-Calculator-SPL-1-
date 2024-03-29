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

void Term::reset()
{
    isEqualSign = false;
    isOperator = false;
    isBrace = false;
    isConstant = false;
    isFraction = false;
    hasHardVal = false;

    awperator.clear();
    brace.clear();

    co_efficient = 0;
    hard_value = 0.0;
    co_efficient_fraction[0] = 1;
    co_efficient_fraction[1] = 1;

    variable_and_exponent.clear();
}
