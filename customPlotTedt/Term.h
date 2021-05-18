#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#ifndef TERM_H
#define TERM_H

class Term
{
public:
    Term();
    int get_variable_count();
    bool isEmpty();

    bool isEqualSign = false;
    bool isOperator = false;
    string awperator;

    bool isBrace = false;
    string brace;

    bool isConstant = false;
    bool isFraction = false;

    int co_efficient = 1;
    int co_efficient_fraction[2];

    vector< pair <string, int> > variable_and_exponent;
};

#endif // TERM_H
