#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3

char *prog;         /* points to the expression to be analyzed */
char input[100];    // global input container
char token[100];    // global token container
int token_type;     // global token type container

struct term												// Experimental area
{														// at the declaration stage 
    bool isConst;										// this structure is a experimantal
	bool isBraces;										// structure to separate a given expression	
	char braceType;										// into algebraic terms.
														// terms contain a co-efficient 
    vector < pair <char, int> > variable_list; 			// a list of variables along with respective exponent
	string leadingOperator;								// and a short chek if its a constant term or not
    int constant;										// and a string to contain the leading opearator
};														// for the sake of handling braces; braces will also be included
														// in the term structure
vector <term> term_container;							// GLOBALLY MANAGED CONTAINER FOR TERMS

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
	if(strchr(" +-/*%^=(){}[]", c) || c == 9 || c == '\r' || c == 0 || c == '\n')
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

	if(strchr("+-*/%^=(){}[]", *prog)) {
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

////// EXPERIMENTAL AREA //////

// make term takes a small list of toekns and returns a term structure//
term make_term(vector <int> type, vector <string> token, int size, string leadingOperator){
	struct term finalTerm;              //...........................................// final return value

	bool foundExponetSign = false;		//...........................................// boolean trigger for exponential sign token
	bool foundVariable = false;			//...........................................// boolean trigger for vaiable cahr
	bool foundNumber = false;			//...........................................// boolean trigger for number value
	bool foundMultiplicationSign = false;//..........................................// boolean trigger for multiplication sign token
	bool foundDivisionSign = false;		//...........................................// boolean trigger for division sign token

	int value = 0;				//...................................................// temporary container for number value
	char variableChar = '\0';   //...................................................// temporary container for charecter variable

	for(int i=0; i<size; ++i)           //...........................................// initializing loop to separate co-efficeint from exponent
	{
		// Special term containing only braces
		if(strchr("(){}[]", token[i][0]))
		{
			finalTerm.isBraces = true;
			finalTerm.braceType = token[i][0];
			break;
		}
		// end of special if step	


		// initially storing in temporary container 
		if (type[i] == NUMBER)
		{ 
			value = token_to_int(token[i]);
			foundNumber = true;
		}
		else if (type[i] == DELIMITER)
		{
			if(token[i][0] == '^')	
			{
				foundExponetSign = true;
				continue;
			}
		}
		else if (type[i] == VARIABLE)
		{
			if (!foundVariable)
			{
				variableChar = token[i][0];
				foundVariable = true;
					
				if (i < size - 1)	continue;
			}
			else if (foundVariable)
			{
				i--;	//........................................................// repeate this iteration
			}
		}
		// end of the step


		// fill up the variable container
		if (foundVariable)
		{
			if(foundExponetSign)
			{
				if(foundNumber)
				{
					finalTerm.variable_list.push_back(make_pair(variableChar, value));
					
					variableChar = '\0';
					value = 0;

					foundVariable = false;
					foundExponetSign = false;
					foundNumber = false;
				}
			}
			else
			{
				finalTerm.variable_list.push_back(make_pair(variableChar, 1));

				variableChar = '\0';
				value = 0;

				foundVariable = false;
				foundNumber = false;
				foundExponetSign = false;
			}
			
		}
		else if (foundNumber)
		{
			if (finalTerm.constant == 0) finalTerm.constant = value;
			else 						 finalTerm.constant *= value;
		
			foundNumber = false;
		}
	}

	return finalTerm;
}
// end of make term //

// start of packing tokens //

void chek_packing(vector<int> types, vector<string> tokens, string leadingOP){
	cout << " A Pack with leading op: " << leadingOP << endl; 
	for (int i=0; i<types.size(); ++i){
		cout << types[i] << "\t" << tokens[i] << endl;
	}
}


void getAndPackTokens(string inpt){
    vector<string> tokens;
    vector<int> types;
    
    strcpy(input, inpt.c_str());
    prog = input;

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

	vector <int> pack_types;
	vector<string> pack_tokens;
	string leadingOperator = "+";

    for(int i=0; i<tokens.size(); ++i)
    {
        if(types[i] == DELIMITER || i == types.size() - 1)
		{
			if(pack_types.size() > 0) //..........................................................................................// chaking if pack already has something in before prcessing for the new delimiter
			{	
				chek_packing(pack_types, pack_tokens, leadingOperator);
				//term_container.push_back(make_term(pack_types, pack_tokens, pack_types.size(), leadingOperator));
			
				pack_tokens.clear();
				pack_types.clear();
			}

			if(tokens[i][0] == '=') continue; //................................................................................// go to the next container if it has a equal sign

			if(strchr("(){}[]", tokens[i][0])) //...............................................................................// special term containing only braces
			{
				pack_types.push_back(types[i]);
				pack_tokens.push_back(tokens[i]);

				chek_packing(pack_types, pack_tokens, "none");
				//term_container.push_back(make_term(pack_types, pack_tokens, 1));
				
				pack_tokens.clear();
				pack_types.clear();

				continue;
			} //.................................................................................................................// End of special if
			else
			{
				leadingOperator = tokens[i];
				continue;
			}
		}

		pack_types.push_back(types[i]);    //....................................................................................// standard packing of token types
		pack_tokens.push_back(tokens[i]);  //....................................................................................// standard packing of tokens
    }

}




// End of packing tokens //






////// EXPERIMENTAL AREA //////





//// TESTING AREA /////

void getToken_chk(string inpt){
    vector<string> tokens;
    vector<int> types;
    
    strcpy(input, inpt.c_str());
    prog = input;

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

    for(int i=0; i<tokens.size(); ++i)
    {
        if (types[i] == DELIMITER)      cout << "It's Delimeter \t";
        else if (types[i] == VARIABLE) cout << "It's Variable \t";
        else if (types[i] == NUMBER)   cout << "It's Number \t";
        
        cout << "token : " << tokens[i] << "\n"; 
    }

}

void test(){
	string inpt;
    getline(cin, inpt, '\n');

	getAndPackTokens(inpt);
}

///// TESTING AREA /////

int main (void){
    
    test();

    return 0;
}
