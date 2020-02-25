#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

vector<int> simple_integer_parser(char* str){
	vector<int> vec;

	int num = 0;
	bool flag = false;
	for(int i=0; str[i] != '\0'; ++i){
		if(str[i] >= 48 && str[i] <= 57){
			flag = true;
			num = num*10 + (str[i] - '0');
		}
		else if(flag){ 
			vec.push_back(num);
			num = 0;
			flag = false;
		}
		else flag = false;
	}

	return vec;
}

int main(void){
	vector<int> vec;
	char str[100];
	fgets(str,100,stdin);

	vec = simple_integer_parser(str);

	for(int i=0; i<vec.size(); ++i){
		cout << vec[i] << " ";
	}cout << endl;

	return 0;
}


