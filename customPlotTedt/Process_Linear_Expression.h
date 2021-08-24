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

using namespace std;

#ifndef PROCESS_LINEAR_EXPRESSION_H
#define PROCESS_LINEAR_EXPRESSION_H

class Process_Linear_Expression
{
private:
    Parser parser;
    Algebraic_Opeartion algebraic_opeartion;

public:
    /*Data*/
    vector <Term> initial_input;

    Process_Linear_Expression();

    void get_input (string str_input);
    void get_input (vector <Term> vec_input);
    Term reverse_operator (Term input);
    vector <Term> separate_variable_constant (vector <Term> input_line);
    vector <Term> shorten_each_side (vector <Term> input_line);
    vector <vector <Term>> solve ();

    // testing utility
    string print_line(vector<Term> container);
    void clear_all();
};

#endif // PROCESS_LINEAR_EXPRESSION_H
