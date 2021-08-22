#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "Term.h"
#include "Parser.h"
#include "Algebraic_Opeartion.h"
#include "Process_Linear_Expression.h"

using namespace std;

#ifndef PROCESS_QUADRATIC_EQUATION_H
#define PROCESS_QUADRATIC_EQUATION_H


class Process_Quadratic_Equation
{
private:
    Parser parser;
    Algebraic_Opeartion algebraic_operation;
    Process_Linear_Expression process_linear_expression;

public:
    Process_Quadratic_Equation();

    vector <Term> initial_equation;
    vector <vector <Term>> factor_eqations;

    // Input functions
    void get_input (string str_input);
    void get_input (vector <Term> vec_input);

    // Utility functions
    int find_highest_exponent (vector <Term> input);
    bool isQuadraticEqation ();
    bool isQuadraticEqation (vector <Term> input);
    Term reverse_operator (Term input);

    // Standard form conversion functions
    vector <Term> substitution_of_terms (vector <Term> input);
    vector <Term> convert_to_standard_form (vector<Term> input);

    // Remainder theorum implementation functions
    bool cheak_for_integer_root (vector <Term> input);
    pair <int, int> find_int_root (vector <Term> input);
    vector <vector <Term>> remainder_theorum (vector <Term> input);

    // Factor extracting functions
    void extract_factor_equation (vector <Term> input);
    vector <vector <Term>> solve ();

};

#endif // PROCESS_QUADRATIC_EQUATION_H
