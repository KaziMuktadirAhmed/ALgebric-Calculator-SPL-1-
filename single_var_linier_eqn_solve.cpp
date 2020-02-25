#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

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

int gcd_2_int(int a, int b) {
	if (a == 0) return b;
	return gcd_2_int(b % a, a);
}

string reduceFraction(string inpt) {
	string ans = "";
	int *array;
	array = parseFraction(inpt);

	int gcd = gcd_2_int(array[0],array[1]);
	
	array[0] /= gcd;
	array[1] /= gcd;

	if(array[1] != 1)
		ans += (to_string(array[0]) + '/' + to_string(array[1]));
	else
		ans += to_string(array[0]);

	return ans;
}

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
			if(negSign){num *= -1; negSign = false;}

			if(str[i] >= 'a' && str[i] <= 'z'){
				if(isNeg) num *= -1;
				vec[str[i] - 'a'].push_back(num);
			}
			else{
				if(!isNeg) num *= -1; 
				vec[26].push_back(num);
			}
			
			num = 0;
			flag = false;
		}
		else flag = false;

	 	if(str[i] == '-') negSign = true;
	 	if(str[i] == '=') isNeg = true;
	}

	return vec;
}

void single_var_linier_eqn_solve(string inpt){
	vector<int>* vec;
	string implies = "->";
	string fraction,output = "";

	vec = integer_parser(inpt);

	int id,steps,var_count = 0;
	for(int i=0; i<26; ++i){
		if(vec[i].size() > 0){
			++var_count;
			id = i;
		}
	}

	if(var_count > 1){
		cout << "Can't Do it!!!\n";
		return;
	}

	//STEP - 01: separating variables and constant terms
	output = (implies + " ");
	for(int i=0; i<vec[id].size(); ++i){
		if(vec[id][i] < 0) output += ("- " + to_string(abs(vec[id][i])) + (char)(id + 'a') + " ");
		
		else {
			if(i == 0)	   output += (to_string(abs(vec[id][i])) + (char)(id + 'a') + " ");
			else		   output += ("+ " + to_string(abs(vec[id][i])) + (char)(id + 'a') + " ");
		}
	}

	output += "= ";

	for(int i=0; i<vec[26].size(); ++i){
		if(i == 0)				output += (to_string(vec[26][i]) + " ");
		
		else{
			if(vec[26][i] < 0) output += ("- " + to_string(abs(vec[26][i])) + " ");
			else			   output += ("+ " + to_string(abs(vec[26][i])) + " ");
		}
	}
	output += '\n';
	cout << output;
	// end of step 1

	//STEP - 02: Calculating the co-effieicient and constant terms
	output = (implies + " "); 
	int var_sum = 0, const_sum = 0;

	for(int i=0; i<vec[id].size(); ++i) var_sum += vec[id][i];
	for(int i=0; i<vec[26].size(); ++i) const_sum += vec[26][i];

	output += to_string(var_sum) + (char)(id + 'a') + " = " + to_string(const_sum) + "\n";
	cout << output;
	// end of step 2

	// STEP - 03: calculate the value of x
	output = (implies + " " + (char)(id + 'a') + " = ");

	if((const_sum < 0 && var_sum > 0) || (const_sum >= 0 && var_sum < 0)){
		fraction = to_string(abs(const_sum)) + '/' + to_string(abs(var_sum));
		output += "-";
	}
	else
		fraction = to_string(const_sum) + '/' + to_string(var_sum); 
	
	output += reduceFraction(fraction) + '\n';
	cout << output;
	// end of step 3
}

int main(void){
	char str[100];
	fgets(str,100,stdin);
	//cout << str;
	single_var_linier_eqn_solve(str);
	return 0;
}



















































































