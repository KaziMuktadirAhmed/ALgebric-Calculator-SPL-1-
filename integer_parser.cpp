#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

vector<int>* integer_parser(string str){
	static vector<int> vec[27];

	int num = 0;
	bool flag = false, isNeg = false, negSign = false;
	for(int i=0; str[i] != '\0'; ++i){
		if(str[i] >= 48 && str[i] <= 57){
			flag = true;
			num = num*10 + (str[i] - '0');
		}
		else if(flag){
			if(isNeg) num *= -1;
			if(negSign){num *= -1; negSign = false;}

			if(str[i] >= 'a' && str[i] <= 'z')
				vec[str[i] - 'a'].push_back(num);
			else{
				num *= -1;
				vec[26].push_back(num);
			}
			
			num = 0;
			flag = false;
		}
		else if(str[i] == '-') negSign = true;
		else if(str[i] == '=') isNeg = true;
		else flag = false;
	}

	return vec;
}

int main(void){
	vector<int>* vec;
	char str[100];
	fgets(str,100,stdin);

	vec = simple_integer_parser(str);

	for(int k=0; k<27; ++k){
		if(vec[k].size() > 0){
			cout << (char)(k+'a') << ": ";

			for(int i=0; i<vec[k].size(); ++i){
				cout << vec[k][i] << " ";
			}

			cout << endl;
		}
	}

	return 0;
}