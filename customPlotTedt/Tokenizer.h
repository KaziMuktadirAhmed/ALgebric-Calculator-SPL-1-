#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#ifndef TEST_H
#define TEST_H

class Tokenizer
{
private:
    const int OPERATOR = 1;
    const int VARIABLE = 2;
    const int NUMBER = 3;
    const int BRACES = 4;
    const int EXPONENT_SIGN = 5;
    const int EQUAL_SIGN = 6;

    char *prog;         /* points to the expression to be analyzed */
    char input[100];    // global input container
    char token[100];    // global token container
    int token_type;     // global token type container

    bool is_alphabte(int str);
    bool is_digit(int str);
    bool is_delimiter(char c);
    void get_token(void);
    void tokenize_input(string inpt);

public:
    Tokenizer();

    vector<string> tokens;
    vector<int> types;

    unsigned int length = types.size();

    // User interface part
    void start(string user_input);

    // Utility functions
    int get_token_count();
    void testTokenizer();
    void clear_data();

};

#endif // TEST_H
