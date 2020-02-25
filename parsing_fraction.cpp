#include <iostream>
using namespace std;

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

int main(void){
	int* fraction;
	string str;
	cin >> str;

	fraction = parseFraction(str);
	cout << fraction[0] << " " << fraction[1] << '\n';

	return 0;
}