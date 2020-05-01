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

		tokens.push_back(token);
        types.push_back(token_type);
	}

    bool passedEqualSign = false;
    bool passedNegSign = false;
    int num = 0;

    for(int i=0; i<types.size(); ++i){
        if(types[i] == NUMBER){
            num = token_to_int(tokens[i]);
        }
        else if(types[i] == VARIABLE){
            if(num == 0) num = 1;

            if(passedEqualSign) num *= -1;
            if(passedNegSign) {num *= -1; passedNegSign = false;}

            vec[tokens[i][0] - 'a'].push_back(num);
        }
        else if(types[i] == DELIMITER){
            if(num != 0) vec[26].push_back(num);

            if(tokens[i][0] == '=') passedEqualSign = true;
            if(tokens[i][0] == '-') passedNegSign = true;
        }
    }
}


int main(void)
{
	fgets(input,100,stdin);
	prog = input;

	separate_term();

	return 0;
}