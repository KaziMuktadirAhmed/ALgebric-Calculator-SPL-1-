#include "Handle_Fractions.h"

int *Handle_Fractions::parseFraction(string inpt)
{
    int isDiv = 0;
    static int fraction[2] = { 0,0 };

    for (int i = inpt.length()-1, j = 1; i>=0; --i) {
        if (inpt[i] == '/') {
            j = 1;
            isDiv = 1;
            continue;
        }

        if (isDiv == 0) {
            fraction[1] += j * (inpt[i] - '0');
            j *= 10;
        }
        else {
            fraction[0] += j * (inpt[i] - '0');
            j *= 10;
        }
    }

    return fraction;
}

int Handle_Fractions::gcd_2_int(int a, int b)
{
    if (a == 0) return b;
    return gcd_2_int(b % a, a);
}

void Handle_Fractions::reduceFraction(int a, int b)
{
    int array[2];

    array[0] = a;
    array[1] = b;

    int gcd = gcd_2_int(array[0],array[1]);

    array[0] /= gcd;
    array[1] /= gcd;

    result[0] = array[0];
    result[1] = array[1];
}

Handle_Fractions::Handle_Fractions()
{

}

void Handle_Fractions::start(int input[])
{
    result[0] = input[0];
    result[1] = input[1];

    reduceFraction(result[0], result[1]);

    input[0] = result[0];
    input[1] = result[1];
}
