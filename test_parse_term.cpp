#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Tokenizer
{
private:
	const int OPERATOR = 1;
	const int VARIABLE = 2;
	const int NUMBER = 3;
	const int BRACES = 4;
	const int EXPONENT_SIGN = 5;
	const int EQUAL_SIGN = 6;

	char *prog;         /* points to the expression to be analyzed */
	char input[100];    // global input container
	char token[100];    // global token container
	int token_type;     // global token type container

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

		if(strchr("+-*/%", *prog)) {
			token_type = OPERATOR;
			*temp++ = *prog++;		// advance to next char
		}
		else if(strchr("+-*/%^=(){}[]", *prog)) {

			if(strchr("+-*/%", *prog))  // Differentiate the delimeters
				token_type = OPERATOR;
			else if(*prog == '=')
				token_type = EQUAL_SIGN;
			else if(*prog == '^')
				token_type = EXPONENT_SIGN;
			else if(strchr("(){}[]", *prog))			
				token_type = BRACES;

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
			while(!is_delimiter(*prog) && !is_alphabte(*prog) && !isspace(*prog)) 
				*temp++ = *prog++;
			
			token_type = NUMBER;
		}

		*temp = '\0';
	}

	void tokenize_input(string inpt)
	{
    	// vector<string> tokens;
    	// vector<int> types;
    
    	strcpy(input, inpt.c_str());
    	prog = input;

    	while(1){
			if((prog - input) >= strlen(input)) 
				break;

			get_token();

        	string demo;
        	demo.assign(token);

        	if(token_type >= 1 && token_type <= 6){
		    	tokens.push_back(demo);
            	types.push_back(token_type);
        	}
		}
	}	


public:
	Tokenizer() {}
	~Tokenizer() {}

	vector<string> tokens;
    vector<int> types;

    unsigned int length = types.size();	

	void start(string user_input)
	{
		tokenize_input(user_input);
	}

	void testTokenizer()
	{
		if (types.size() == 0){
			cout << "No input given to the Tokenizer.\n";
			return;
		}

		for(int i=0; i<tokens.size(); ++i)
    	{
        	if(types[i] == OPERATOR)      cout << "It's Operator \t";
        	else if (types[i] == VARIABLE) cout << "It's Variable \t";
        	else if (types[i] == NUMBER)   cout << "It's Number \t";
			else if (types[i] == BRACES)   cout << "It's Braces \t";
			else if (types[i] == EQUAL_SIGN)   cout << "It's Equal sign \t";
			else if (types[i] == EXPONENT_SIGN)   cout << "It's Exponent sign \t";
        	
        	cout << "token : " << tokens[i] << "\n"; 
    	}
	}

	void clear_data()
	{
		tokens.clear();
		types.clear();
	}

};

class Term
{
private:
    /* data */
public:
    Term(/* args */) {}
    ~Term() {}

	bool isEqualSign = false;
    bool isOperator = false;
    string awperator;

    bool isBrace = false;
    string brace;

    bool isConstant = false;

    int co_efficient = 1;
    vector< pair <string, int> > variable_and_exponent;
};

class Parser
{
private:
    const int OPERATOR = 1;
	const int VARIABLE = 2;
	const int NUMBER = 3;
	const int BRACES = 4;
	const int EXPONENT_SIGN = 5;
	const int EQUAL_SIGN = 6;

	int start_index = 0;
	bool get_term_flag = false;

	Tokenizer tokenized_input;

	int token_to_int(string temp)
	{
    	int toNum = 0;

    	for	(int i=0; temp[i] != '\0'; ++i)
        	toNum = toNum*10 + (temp[i]-'0');
    
    	return toNum;
	}

	Term get_term(int token_count)
	{
		Term demo;

		if (tokenized_input.types[start_index] == OPERATOR) {  
			demo.isOperator = true;
			demo.isEqualSign = false;                                     /* Separating  the operator */
			demo.isBrace = false;
			demo.isConstant = false;

			demo.awperator = tokenized_input.tokens[start_index];
			++start_index;
		}
		else if (tokenized_input.types[start_index] == EQUAL_SIGN) {
			demo.isOperator = false;
			demo.isEqualSign = false;                                     /* Separating  the equal operator */
			demo.isBrace = true;
			demo.isConstant = false;

			demo.awperator = tokenized_input.tokens[start_index];
			++start_index;
		}
		else if (tokenized_input.types[start_index] == BRACES) {
			demo.isOperator = false;
			demo.isEqualSign = false;                                     /* Separating  the braces */
			demo.isBrace = true;
			demo.isConstant = false;

			demo.brace = tokenized_input.tokens[start_index];
			++start_index;
		}
		else {
			if (tokenized_input.types[start_index] == NUMBER) {
				if (start_index == token_count - 1) {
					demo.isOperator = false;
					demo.isEqualSign = false;
					demo.isBrace = false;
					demo.isConstant = true;

					demo.co_efficient = token_to_int(tokenized_input.tokens[start_index]);
					++start_index;
				}
				else if (tokenized_input.types[start_index + 1] != VARIABLE) {
					demo.isOperator = false;
					demo.isEqualSign = false;
					demo.isBrace = false;
					demo.isConstant = true;

					demo.co_efficient = token_to_int(tokenized_input.tokens[start_index]);

					if (tokenized_input.types[start_index + 1] == EXPONENT_SIGN)
						get_term_flag = true;
					
					++start_index;
				}
				else {
					demo.isOperator = false;
					demo.isEqualSign = false;
					demo.isBrace = false;
					demo.isConstant = false;

					demo.co_efficient = token_to_int(tokenized_input.tokens[start_index]);   /* Separating the constant in term */
					++start_index;

					while (start_index < token_count) {
						if (tokenized_input.types[start_index] == OPERATOR || tokenized_input.types[start_index] == BRACES || tokenized_input.types[start_index] == EQUAL_SIGN)
							break;

						if (tokenized_input.types[start_index] == VARIABLE) {
							pair<string, int> temp;
							temp.first = tokenized_input.tokens[start_index];
							//++start_index;

								if (tokenized_input.types[start_index + 1] == EXPONENT_SIGN && start_index + 1 < token_count) {
									++start_index;

									if (tokenized_input.types[start_index + 1] == NUMBER && start_index + 1 < token_count) {
										++start_index;
										temp.second = token_to_int(tokenized_input.tokens[start_index]);
									}
								}
								else {
									temp.second = 1;
								}

							demo.variable_and_exponent.push_back(temp);
							++start_index;
						}
					}
				}
			}
			else if (tokenized_input.types[start_index] == EXPONENT_SIGN) {
				if (get_term_flag) {
					demo.isOperator = true;
					demo.isEqualSign = false;                                     /* Separating  the special exponent operator */
					demo.isBrace = false;
					demo.isConstant = false;

					demo.awperator = tokenized_input.tokens[start_index];
					++start_index;
				}
			}
			else if (tokenized_input.types[start_index] == VARIABLE) {
				demo.isOperator = false;
				demo.isEqualSign = false;
				demo.isBrace = false;
				demo.isConstant = false;

				while (start_index < token_count) {
					if (tokenized_input.types[start_index] == OPERATOR || tokenized_input.types[start_index] == BRACES || tokenized_input.types[start_index] == EQUAL_SIGN)
						break;

					if (tokenized_input.types[start_index] == VARIABLE) {
						pair<string, int> temp;
						temp.first = tokenized_input.tokens[start_index];
						//++start_index;

						if (tokenized_input.types[start_index + 1] == EXPONENT_SIGN && start_index + 1 < token_count) {
							++start_index;

							if (tokenized_input.types[start_index + 1] == NUMBER && start_index + 1 < token_count) {
								++start_index;
								temp.second = token_to_int(tokenized_input.tokens[start_index]);
							}
						}
						else {
							temp.second = 1;
						}

						demo.variable_and_exponent.push_back(temp);
						++start_index;
					}
				}

			}
		} 
		
		return demo;
	}

	void clear_pair(pair <char, int> &pr) {
		pr.first = '\0';
		pr.second = 0;
	}

public:
    Parser(/* args */) {}
    ~Parser() {}

	vector <Term> terms; // Cx^n .... braces ...... operators ... constant

	void take_input(string user_input)
	{
		Term temp;

		tokenized_input.start(user_input);
		tokenized_input.testTokenizer();
		temp = get_term(tokenized_input.tokens.size());

		cout << temp.co_efficient << " ";
		for(int i=0; i<temp.variable_and_exponent.size(); ++i)
			cout << temp.variable_and_exponent[i].first << "^" << temp.variable_and_exponent[i].second << " "; 
	}	

};










int main(void)
{
	// Tokenizer t1;
	Parser p1;

	string inpt;
    getline(cin, inpt, '\n');

    // t1.start(inpt);
	p1.take_input(inpt);

	return 0;
}
