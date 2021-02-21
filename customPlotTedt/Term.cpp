#include "Term.h"

Term::Term()
{

}

int Term::get_variable_count()
{
    return Term::variable_and_exponent.size();
}
