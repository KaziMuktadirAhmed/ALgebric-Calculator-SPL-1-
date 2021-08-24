#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "Tokenizer.h"
#include "Term.h"

using namespace std;

#ifndef PARSER_H
#define PARSER_H


class Parser
{
private:
    const int OPERATOR = 1;
    const int VARIABLE = 2;
    const int NUMBER = 3;
    const int BRACES = 4;
    const int EXPONENT_SIGN = 5;
    const int EQUAL_SIGN = 6;

    int start_index = 0;
    bool get_term_flag = false;

    Tokenizer tokenized_input;

    // Utility functions
    int token_to_int(string temp);
    void clear_pair(pair <char, int> &pr);
    void test_parse_term();
    void test_term_container(vector <Term> terms);

    // Parsing functions
    Term get_term(int token_count);
    void parse_term();

public:
    //term container (the topings of the pizza)
    vector <Term> terms;

    Parser();

    // User interface part
    void take_input(string user_input);
    void clear_all ();
};

#endif // PARSER_H
