#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#ifndef HANDLE_FRACTIONS_H
#define HANDLE_FRACTIONS_H


class Handle_Fractions
{
private:
   int result[2];

   int* parseFraction(string inpt);
   int gcd_2_int(int a, int b);
   void reduceFraction(int a, int b);


public:
    Handle_Fractions();
    void start (int input[]);
};

#endif // HANDLE_FRACTIONS_H
