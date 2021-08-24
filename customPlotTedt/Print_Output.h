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
#include "Process_Quadratic_Expression.h"

using namespace std;

#ifndef PRINT_OUTPUT_H
#define PRINT_OUTPUT_H


class Print_Output
{
public:
    string inital_input_str = "";
    vector <Term> initial_input_line;

    Print_Output();
    void take_input_from_ui(string input);
    void clear_all();
    string solve();

private:
    Parser parser;
    Algebraic_Opeartion algebraic_operation;
    Process_Linear_Expression process_linear_expression;
    Process_Quadratic_Equation process_quadratic_expression;

    string print_line(vector<Term> container);
};

#endif // PRINT_OUTPUT_H
