#include <bits/stdc++.h>

using namespace std;

void converter(int num){
	int root_int,root_conjugate,div_int;
	double div_double;

	root_int = sqrt(num);

	if(root_int*root_int == num){
		cout << root_int;
		return;
	}

	for(; root_int >= 1; root_int--){
		div_int = num/(root_int*root_int);
		div_double = (double)num/(double)(root_int*root_int);
		div_double -= div_int;

		if(div_double == 0)
			break;
	}

	root_conjugate = num/(root_int*root_int);

	if(root_int == 1)
		cout << '/' << num;
	else
		cout << root_int << '/' << root_conjugate << endl;
}

int main(void){
	int n;
	
	cin >> n;
        
	converter(n);

    return 0;
}
