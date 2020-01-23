#include <iostream>
using namespace std;

int gcd_2_int(int a, int b) {
	if (a == 0) return b;
	return gcd_2_int(b % a, a);
}

int lcm_2_int(int a, int b) {
	int lcm;
	lcm = (a*b) / gcd_2_int(a,b);
	return lcm;
}

int gcd_n_int(int arr[], int n) {
	int gcd = arr[0];

	for (int i = 1; i < n; ++i) {
		gcd = gcd_2_int(gcd , arr[i]);	
		if (gcd == 1) return 1;
	}
	return gcd;
}

int lcm_n_int(int arr[], int n) {
	int lcm = arr[0];

	for (int = 1; i < n; ++i) {
		lcm = ((arr[i]*lcm) / (gcd_2_int(arr[i] , lcm)));
	}

	return lcm;
}


int main(void) {
	return 0;
}