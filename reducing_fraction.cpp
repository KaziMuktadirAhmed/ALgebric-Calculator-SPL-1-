#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

/*
	Parsing function to find 
	two integer values from a 
	string input.
*/
int* parseFraction(string inpt) {
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

//GCD for 2 integers
int gcd_2_int(int a, int b) {
	if (a == 0) return b;
	return gcd_2_int(b % a, a);
}

//GCD for n Integers
/*int gcd_n(int inpt[], int size) {
}*/

//Function to reduce fraction
void reduceFraction(string inpt) {
	int *array;
	array = parseFraction(inpt);

	int gcd = gcd_2_int(array[0],array[1]);
	
	array[0] /= gcd;
	array[1] /= gcd;

	cout << array[0] << '/' << array[1];
}

int main(void) {
	string fracton;
	cin >> fracton;
	
	reduceFraction(fracton);

	return 0;
}