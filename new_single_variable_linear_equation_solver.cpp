#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3

char *prog;         /* points to the expression to be analyzed */
char input[100];    // global input container
char token[100];    // global token container
int token_type;     // global token type container

vector<int> vec[27]; // global container for expression handeling

bool is_alphabte(int str)
{
	if((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
		return true;
	else
		return false;
}

bool is_digit(int str)
{
	if(str >= '0' && str <= '9')
		return true;
	else
		return false;
}

bool is_delimiter(char c)
{
	if(strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0 || c == '\n')
		return true;
	else
		return false;
}

// Retruns the next token 
void get_token(void)
{
	register char *temp;
	token_type = 0;
	temp = token;
	*temp = '\0';

	while(isspace(*prog)) ++prog; // skip over the white space

	if(*prog == '\0') {
		token_type = 0;
		return;
	} // at the end of expression

	if(strchr("+-*/%^=()", *prog)) {
		token_type = DELIMITER;
		*temp++ = *prog++;		// advance to next char
	}
	else if(is_alphabte(*prog)) {
		/*
			The following loop is to handel variable name with multiple charecter
		*/
		//while(!is_delimiter(*prog) && !is_digit(*prog) && !isspace(*prog)) *temp++ = *prog++; 
		
		token_type = VARIABLE;
		*temp++ = *prog++;
	}
	else if(is_digit(*prog)) {
		while(!is_delimiter(*prog) && !is_alphabte(*prog) && !isspace(*prog)) *temp++ = *prog++;
		token_type = NUMBER;
	}

	*temp = '\0';
}

int token_to_int(string temp){
    int toNum = 0;

    for(int i=0; temp[i] != '\0'; ++i)
        toNum = toNum*10 + (temp[i]-'0');
    
    return toNum;
}

void separate_term(){
    vector<string> tokens;
    vector<int> types;
    
    while(1){
		if((prog - input) >= strlen(input)) break;
		get_token();

        string demo;
        demo.assign(token);

        if(token_type >= 1 && token_type <= 3){
		    tokens.push_back(demo);
            types.push_back(token_type);
        }
	}

    bool passedEqualSign = false;
    bool passedNegSign = false;
    int num = 0;

    for(int i=0; i<types.size(); ++i){
        if(types[i] == NUMBER){
            num = token_to_int(tokens[i]);

            if(i == types.size() - 1){ 
                if(!passedEqualSign) num *= -1;
                if(passedNegSign) {num *= -1; passedNegSign = false;}
                
                vec[26].push_back(num);
            }
        }
        else if(types[i] == VARIABLE){
            if(num == 0) num = 1;

            if(passedEqualSign) num *= -1;
            if(passedNegSign) {num *= -1; passedNegSign = false;}

            vec[tokens[i][0] - 'a'].push_back(num);
            num = 0;
        }
        else if(types[i] == DELIMITER){
            if(num != 0){ 
                if(!passedEqualSign) num *= -1;
                if(passedNegSign) {num *= -1; passedNegSign = false;}

                vec[26].push_back(num);
            }
            num = 0;

            if(tokens[i][0] == '=') passedEqualSign = true;
            if(tokens[i][0] == '-') passedNegSign = true;
        }
    }
}

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

string single_var_linier_eqn_solve(string inpt){

    strcpy(input, inpt.c_str());
    prog = input;

    string implies = "->";
    string fraction, output = "", variable = "";

    output += "# " + inpt;

    separate_term();

    int id,steps,var_count = 0;
    for(int i=0; i<26; ++i){
        if(vec[i].size() > 0){
            ++var_count;
            id = i;
        }
    }

    if(var_count > 1){
        return "Can't Do it!!!\n";
    }

    //Setting the variable for the equation
    variable += (char)(id + 'a');

    //STEP - 01: separating variables and constant terms
    output += (implies + " ");
    for(int i=0; i<vec[id].size(); ++i){
        if(vec[id][i] < 0){
            if(vec[id][i] < -1) output += ("- " + to_string(abs(vec[id][i])) + variable + " ");
            else                output += ("- " + variable + " ");
        }
        else {
            if(i == 0){
                if(vec[id][i] > 1)   output += (to_string(abs(vec[id][i])) + variable + " ");
                else                 output += (variable + " ");
            }
            else{
                if(vec[id][i] > 1)   output += ("+ " + to_string(abs(vec[id][i])) + variable + " ");
                else                 output += ("+ " + variable + " ");
            }
        }
    }

    output += "= ";

    for(int i=0; i<vec[26].size(); ++i){
        if(i == 0)             output += (to_string(vec[26][i]) + " ");
        
        else{
            if(vec[26][i] < 0) output += ("- " + to_string(abs(vec[26][i])) + " ");
            else               output += ("+ " + to_string(abs(vec[26][i])) + " ");
        }
    }
    output += '\n';
    // end of step 1

    //STEP - 02: Calculating the co-effieicient and constant terms
    output += (implies + " ");
    int var_sum = 0, const_sum = 0;

    for(int i=0; i<vec[id].size(); ++i) var_sum += vec[id][i];
    for(int i=0; i<vec[26].size(); ++i) const_sum += vec[26][i];

    if(var_sum == 0) { return "Invalid Equation\n";}

    if(var_sum > 1 || var_sum < -1)     output += to_string(var_sum) + variable + " = " + to_string(const_sum) + "\n";
    else if(var_sum == 1)               output += variable + " = " + to_string(const_sum) + "\n";
    else if (var_sum == -1)             output += "-" + variable + " = " + to_string(const_sum) + "\n";
    // end of step 2

    // STEP - 03: calculate the value of x
    output += (implies + " " + variable + " = ");

    if((const_sum < 0 && var_sum > 0) || (const_sum >= 0 && var_sum < 0)){
        fraction = to_string(abs(const_sum)) + '/' + to_string(abs(var_sum));
        output += "-";
    }
    else
        fraction = to_string(abs(const_sum)) + '/' + to_string(abs(var_sum)); 
    
    output += reduceFraction(fraction) + '\n';
    // end of step 3

    return output;
}

void cheak_container(){
    for(int i=0; i<27; ++i){
        if(vec[i].size() > 0){
            
            if(i == 26)    cout << "Const: ";
            else           cout << (char)('a' + i) << ": ";

            for(int k=0; k<vec[i].size(); ++k) cout << vec[i][k] << " ";
            cout << endl;
        
        }
    }
}

int main(void)
{
    char str[100];
	fgets(str,100,stdin);
	
    string input_string(str), output;

	output = single_var_linier_eqn_solve(input_string);

    cout << output;
    cheak_container();

	return 0;
}
