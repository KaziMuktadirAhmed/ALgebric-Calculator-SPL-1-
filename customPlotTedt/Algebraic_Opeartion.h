#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "Term.h"
#include "Handle_Fractions.h"

using namespace std;

#ifndef ALGEBRAIC_OPEARTION_H
#define ALGEBRAIC_OPEARTION_H


class Algebraic_Opeartion
{
public:
    Algebraic_Opeartion();

    int is_operable(Term a, Term b);

    // Basic operations

    Term add_term (Term A, Term B);
    Term sub_term (Term A, Term B);
    Term mul_term (Term A, Term B);
    Term div_term (Term A, Term B);

    // Normalizing utility functions

    void shroten_terms (Term &container);
    void normalize_terms (vector <Term> &container);

    Term multiply_operator (Term op_a, Term op_b);
    bool compare_term (Term term1, Term term2);
    bool compare_line (vector <Term> line1, vector<Term> line2);

};

#endif // ALGEBRAIC_OPEARTION_H
