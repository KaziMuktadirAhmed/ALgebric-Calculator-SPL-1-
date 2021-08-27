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

    int get_token_count()
	{
		return types.size();
	}

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
	bool isFraction = false;
	bool hasHardVal = false;

    int co_efficient = 1;
	int co_efficient_fraction[2];

	double hard_value = 0.0;

    vector< pair <string, int> > variable_and_exponent;

	int get_variable_count() 
	{
		return variable_and_exponent.size();
	}

	bool isEmpty()
	{
		if (isEqualSign == false && isOperator == false && isBrace == false && isConstant == false && isFraction == false)
			if (variable_and_exponent.size() == 0)
				return true;

		return false; 	
	}

	void reset() 
	{
		isEqualSign = false;
		isOperator = false;
		isBrace = false;
		isConstant = false;
		isFraction = false;
		hasHardVal = false;

		awperator.clear();
		brace.clear();
		
		co_efficient = 0;
		hard_value = 0.0;
		co_efficient_fraction[0] = 0;
		co_efficient_fraction[1] = 0;

		variable_and_exponent.clear();
	}
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
			demo.isEqualSign = true;                                     /* Separating  the equal operator */
			demo.isBrace = false;
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

			if (tokenized_input.types[start_index + 1] == EXPONENT_SIGN && start_index + 1 < token_count) {
				string comp = tokenized_input.tokens[start_index];

				if (comp.compare(")") == 0 || comp.compare("}") == 0 || comp.compare("]") == 0) {
					get_term_flag = true;
				}
				else {
					cout << "False input\n";
				}
			}

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

									int sign = 1;

									if (tokenized_input.types[start_index + 1] == OPERATOR && start_index + 1 < token_count) {
										if (tokenized_input.tokens[start_index + 1].compare("-") == 0) {
											++start_index;
											sign = -1;
										}
									}

									if (tokenized_input.types[start_index + 1] == NUMBER && start_index + 1 < token_count) {
										++start_index;
										temp.second = sign * token_to_int(tokenized_input.tokens[start_index]);
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
					get_term_flag = false;
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

							int sign = 1;

							if (tokenized_input.types[start_index + 1] == OPERATOR && start_index + 1 < token_count) {
								if (tokenized_input.tokens[start_index + 1].compare("-") == 0) {
									++start_index;
									sign = -1;
								}
							}

							if (tokenized_input.types[start_index + 1] == NUMBER && start_index + 1 < token_count) {
								++start_index;
								temp.second = sign * token_to_int(tokenized_input.tokens[start_index]);
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

	void parse_term() 
	{
		Term demo;
		int token_count = tokenized_input.get_token_count();

		start_index = 0;

		while (start_index < token_count) {
			demo = get_term(token_count);
			terms.push_back(demo); 	
		}
	}

public:
    Parser(/* args */) {}
    ~Parser() {}

	vector <Term> terms; // Cx^n .... braces ...... operators ... constant

	void take_input(string user_input)
	{
		tokenized_input.start(user_input);
		parse_term();
	}

	void test_parse_term()
	{
		for(int i=0; i<terms.size(); ++i) {
			if (terms[i].isOperator)
				cout << "Term type: operator.\tTerm: " << terms[i].awperator << endl;
			else if (terms[i].isBrace)
				cout << "Term type: Brace.\tTerm: " << terms[i].brace << endl;
			else if (terms[i].isEqualSign)
				cout << "Term type: eqaul_sign.\tTerm: " << terms[i].awperator << endl;
			else if (terms[i].isConstant)
				cout << "Term type: constant.\tTerm: " << terms[i].co_efficient << endl;
			else {
				cout << "Term type: Cx^n.\tTerm: " << terms[i].co_efficient << "  ";

				for(int j=0; j<terms[i].get_variable_count(); ++j) {
					cout << terms[i].variable_and_exponent[j].first << "^" << terms[i].variable_and_exponent[j].second << " ";
				} cout << endl;
			}
		}
	}

	void test_term_container(vector <Term> terms)
	{
		for(int i=0; i<terms.size(); ++i) {
			if (terms[i].isOperator)
				cout << "Term type: operator.\tTerm: " << terms[i].awperator << endl;
			else if (terms[i].isBrace)
				cout << "Term type: Brace.\tTerm: " << terms[i].brace << endl;
			else if (terms[i].isEqualSign)
				cout << "Term type: eqaul_sign.\tTerm: " << terms[i].awperator << endl;
			else if (terms[i].isConstant)
				cout << "Term type: constant.\tTerm: " << terms[i].co_efficient << endl;
			else {
				cout << "Term type: Cx^n.\tTerm: " << terms[i].co_efficient << "  ";

				for(int j=0; j<terms[i].get_variable_count(); ++j) {
					cout << terms[i].variable_and_exponent[j].first << "^" << terms[i].variable_and_exponent[j].second << " ";
				} cout << endl;
			}
		}
	}

	void clear_all()
	{
    	terms.clear();
    	start_index = 0;
    	get_term_flag = false;
    	tokenized_input.clear_data();
	}
};

class Handle_Fractions
{
private:
	/* data */
	int result[2]; 

	/*
		Parsing function to find 
		two integer values from a 
		string input.
	*/
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

	//GCD for 2 integers
	int gcd_2_int(int a, int b) {
		if (a == 0) return b;
		return gcd_2_int(b % a, a);
	}

	//Function to reduce fraction
	void reduceFraction(int a, int b) {
		int array[2];

		array[0] = a;
		array[1] = b;

		int gcd = gcd_2_int(array[0],array[1]);
	
		array[0] /= gcd;
		array[1] /= gcd;

		result[0] = array[0];
		result[1] = array[1];
	}

public:
	Handle_Fractions(/* args */) {}
	~Handle_Fractions() {}


	void start (int input[]) {
		result[0] = input[0];
		result[1] = input[1];

		reduceFraction(result[0], result[1]);

		input[0] = result[0];
		input[1] = result[1];
	}
};

class Algebraic_Operation
{
private:

public:
	Algebraic_Operation(/* args */) {}
	~Algebraic_Operation() {}

	int is_operable(Term a, Term b)
	{
		/* 
			The funtion takes 2 term a and b as input. depending on the input the funtion
			retuns a integer value between -1 to 3. They represent

			-1 = inoperable condition (a or b contains brace/equalSign/operator)
			0  = can only perform multiplication or division (either a  or b is constant)
			1  = all operation can be performed (both a and b are constant)
			2  = all operation can be performed (both a and b has same variable and exponent list)
			3  = can only perform multiplication or division (a and b contains diffrent set of variable and exponents)
		*/

		if(a.isBrace || b.isBrace)
			return -1;
		else if (a.isEqualSign || b.isEqualSign)
			return -1;
		else if (a.isOperator || b.isOperator)
			return -1;
		else if (a.isConstant && !(b.isConstant) )
			return 0;
		else if (!(a.isConstant) && b.isConstant)
			return 0;
		else if (a.isConstant && b.isConstant)
			return 1;
		else {
			bool flag = true;

			if (a.get_variable_count() != b.get_variable_count())
				flag = false;
			else {
				for (int i=0; i<a.get_variable_count(); ++i) {
					if (a.variable_and_exponent[i].first.compare(b.variable_and_exponent[i].first) != 0)
						flag = false;
					else if(a.variable_and_exponent[i].second != b.variable_and_exponent[i].second)
						flag = false;

					if (flag == false)
						break;
				}
			}

			if (flag)
				return 2;
			else
				return 3;
		}
	}

	Term add_term (Term A, Term B)
	{
		int comparator_value = is_operable(A, B);

		Term result;

		if (comparator_value == 1) {
			result.isConstant = true;
			result.co_efficient = A.co_efficient + B.co_efficient;
		}
		else if (comparator_value == 2) {
			result.co_efficient = A.co_efficient + B.co_efficient;

			for (int i=0; i<A.get_variable_count(); ++i)
				result.variable_and_exponent.push_back(A.variable_and_exponent[i]);
		}

		return result;
	}

	Term sub_term (Term A, Term B)
	{
		int comparator_value = is_operable(A, B);

		Term result;

		if (comparator_value == 1) {
			result.co_efficient = A.co_efficient - B.co_efficient;

			if (result.co_efficient != 0)
				result.isConstant = true;
		}
		else if (comparator_value == 2) {
			result.co_efficient = A.co_efficient - B.co_efficient;

			if (result.co_efficient != 0) {
				for (int i=0; i<A.get_variable_count(); ++i)
					result.variable_and_exponent.push_back(A.variable_and_exponent[i]);
			}
		}

		return result;
	}

	Term mul_term (Term A, Term B) 
	{
		int comparator_value = is_operable(A, B);
		
		Term result;
		
		if (comparator_value == 1) {
			result.isConstant = true;
			result.co_efficient = A.co_efficient * B.co_efficient;
		}
		else if (comparator_value > -1) {
			result.co_efficient = A.co_efficient * B.co_efficient;

			for (int i=0; i<A.get_variable_count(); ++i)
				result.variable_and_exponent.push_back(A.variable_and_exponent[i]);

			for (int i=0; i<B.get_variable_count(); ++i)
				result.variable_and_exponent.push_back(B.variable_and_exponent[i]);

			shroten_terms(result);
		}

		return result;
	}

	Term div_term (Term A, Term B) 
	{
		int comparator_value = is_operable(A, B);
		
		Term result;
		int temp_fraction[2];
		pair <string, int> temp_pr;

		Handle_Fractions reduce_fraction;

		if (comparator_value == 1) {
			result.isConstant = true;

			if(A.co_efficient % B.co_efficient != 0) {

				temp_fraction[0] = A.co_efficient;
				temp_fraction[1] = B.co_efficient;

				reduce_fraction.start(temp_fraction);

				if (temp_fraction[1] < 0 && temp_fraction[0] > 0) {
					temp_fraction[0] *= -1;
					temp_fraction[1] *= -1;
				}

				result.isFraction = true;
				result.co_efficient_fraction[0] = temp_fraction[0];
				result.co_efficient_fraction[1] = temp_fraction[1];
			}
			else {
				result.co_efficient = A.co_efficient / B.co_efficient;
			}
		}
		else if (comparator_value > -1) {

			if(A.co_efficient % B.co_efficient != 0) {

				temp_fraction[0] = A.co_efficient;
				temp_fraction[1] = B.co_efficient;

				reduce_fraction.start(temp_fraction);

				if (temp_fraction[1] < 0 && temp_fraction[0] > 0) {
					temp_fraction[0] *= -1;
					temp_fraction[1] *= -1;
				}

				result.isFraction = true;
				result.co_efficient_fraction[0] = temp_fraction[0];
				result.co_efficient_fraction[1] = temp_fraction[1];
			}
			else {
				result.co_efficient = A.co_efficient / B.co_efficient;
			}

			for (int i=0; i<A.get_variable_count(); ++i)
				result.variable_and_exponent.push_back(A.variable_and_exponent[i]);

			for (int i=0; i<B.get_variable_count(); ++i) {
				// result.variable_and_exponent.push_back(B.variable_and_exponent[i]);

				temp_pr.first = B.variable_and_exponent[i].first;
				temp_pr.second = -1 * B.variable_and_exponent[i].second;

				result.variable_and_exponent.push_back(temp_pr);
			}

			shroten_terms(result);

			for (int i=0; i < result.get_variable_count(); ++i) {
				
				if (result.variable_and_exponent[i].second == 0){
					result.variable_and_exponent.erase( result.variable_and_exponent.begin() + i);
					--i;
				}
			}
		}

		return result;
	}

	Term multiply_operator (Term op_a, Term op_b)
	{
		Term returnVal;
		returnVal.reset();

		if (op_a.isOperator == true && op_b.isOperator == true) {
			returnVal.isOperator = true;

			if (op_a.awperator[0] == op_b.awperator[0])
				returnVal.awperator = "+";
			else 
				returnVal.awperator = "-";
		}

		return returnVal;
	}

	// Normalizing utility functions

	bool compare_term (Term term1, Term term2) 
	{
		bool isEqual = true;

		if (term1.isBrace == term2.isBrace)
			if (term1.brace.compare(term2.brace) != 0)
				isEqual = false;
		else	isEqual = false;
	
		if (term1.isOperator == term2.isOperator)
			if (term1.awperator.compare(term2.awperator) != 0)
				isEqual = false;
		else	isEqual = false;

		if (term1.isEqualSign != term2.isEqualSign)
			isEqual = false;
		
		if (term1.isConstant == term2.isConstant)
			if (term1.co_efficient != term2.co_efficient)
				isEqual = false;
			else {
				shroten_terms(term1);
				shroten_terms(term2);

				if (term1.get_variable_count() != term2.get_variable_count())
					isEqual = false;
				else {
					// bool isVariableEqual = true;
					for (int i=0; i<term1.get_variable_count(); ++i) {
						if (term1.variable_and_exponent[i].first[0] != term2.variable_and_exponent[i].first[0]) {
							isEqual = false;
							break;
						}
						
						if (term1.variable_and_exponent[i].second != term2.variable_and_exponent[i].second) {
							isEqual = false;
							break;
						}
					}	
				}
			}
		else	isEqual = false;

		return isEqual;
	}

	bool compare_line (vector <Term> line1, vector<Term> line2)
	{
		bool isEqual = true;

		if (line1.size() != line2.size())
			isEqual = false;
		else {
			for (int i=0; i < line1.size(); ++i) {
				if (compare_term(line1[i], line2[i])){
					isEqual = false;
					break;
				}
			}
		}

		return isEqual;
	} 

	void shroten_terms (Term &container)
	{
		if (container.get_variable_count() <= 0)
			return;

		/* Initial sorting between variables to smoothen the later calculations */
	
		sort(container.variable_and_exponent.begin(), container.variable_and_exponent.end());

		pair<string, int> pr = container.variable_and_exponent[0];
		vector< pair<string, int> > temp_container;

		for(int i=1; i<container.variable_and_exponent.size(); ++i) {
			if (pr.first.compare(container.variable_and_exponent[i].first) != 0) {
				temp_container.push_back(pr);

				pr.first = container.variable_and_exponent[i].first;
				pr.second = container.variable_and_exponent[i].second;
			} else {
				pr.second += container.variable_and_exponent[i].second;
			}
		} 	temp_container.push_back(pr);

		container.variable_and_exponent.clear();
		container.variable_and_exponent.assign(temp_container.begin(), temp_container.end());
	}

	void normalize_terms (vector <Term> &container)
	{
		for (int i=0; i < container.size(); ++i) {
			shroten_terms(container[i]);
		}
	}
		
};

class Process_Linear_Expression
{
private:
    // Utility functions //
    Parser parser;
    Algebraic_Operation algebraic_opeartion;

public:
    /* data */
    vector <Term> initial_input;

    Process_Linear_Expression(/* args */) {}
    ~Process_Linear_Expression() {}

    void get_input (string str_input) 
    {
		initial_input.clear();
        parser.take_input(str_input);

        for (int i=0; i<parser.terms.size(); ++i)
            initial_input.push_back(parser.terms[i]);

		algebraic_opeartion.normalize_terms(initial_input);
    }

    void get_input (vector <Term> vec_input) 
    {
		initial_input.clear();
        for (int i=0; i<vec_input.size(); ++i)
            initial_input.push_back(vec_input[i]);

		algebraic_opeartion.normalize_terms(initial_input);
    }

    Term reverse_operator (Term input)
    {
        Term result;

        if (input.isOperator == true) {

            if (input.awperator.compare("+") == 0) {
                result.isOperator = true;
                result.awperator = "-";
            }
            else if (input.awperator.compare("-") == 0) {
                result.isOperator = true;
                result.awperator = "+";
            }
            else if (input.awperator.compare("*") == 0) {
                result.isOperator = true;
                result.awperator = "/";
            }
            else if (input.awperator.compare("/") == 0) {
                result.isOperator = true;
                result.awperator = "*";
            }
        }

        return result;
    }

	vector <Term> separate_variable_constant (vector <Term> input_line) 
	{
		int equal_index = 0;
		vector <Term> result, LHS, RHS;

		Term plus_sign, equal_sign, zero;

		plus_sign.isOperator = true;
		plus_sign.awperator = "+";

		equal_sign.isEqualSign = true;
		equal_sign.awperator = "=";

		zero.isConstant = true;
		zero.co_efficient = 0;

		for (int i=0; input_line[i].isEqualSign != true; ++i) {
			// keeping a record of last variable term //
			equal_index = i;

			if (input_line[i].isOperator == false && input_line[i].isBrace == false) {
				// secondary if filter //
				if (input_line[i].isConstant == false) {
					if (i == 0) {
						LHS.push_back(plus_sign);
						LHS.push_back(input_line[i]); 
					}
					else {
						if (input_line[i-1].isOperator == true) 
							LHS.push_back(input_line[i-1]);

						LHS.push_back(input_line[i]);
					}
				}
				else {
					if (i == 0) {
						RHS.push_back(reverse_operator(plus_sign));
						RHS.push_back(input_line[i]);
					}
					else {
						if (input_line[i-1].isOperator == true)
							RHS.push_back(reverse_operator(input_line[i-1]));

						RHS.push_back(input_line[i]);
					}
				}
			}

		}	equal_index++;

		for (int i = equal_index + 1; i<input_line.size(); ++i) {
			
			if (input_line[i].isOperator == false && input_line[i].isBrace == false) {
				// secondary if filter //
				if (input_line[i].isConstant == false) {
					if (i == equal_index + 1) {
						LHS.push_back(reverse_operator(plus_sign));
						LHS.push_back(input_line[i]); 
					}
					else {
						if (input_line[i-1].isOperator == true) 
							LHS.push_back(reverse_operator(input_line[i-1]));

						LHS.push_back(input_line[i]);
					}
				}
				else {
					if (i == equal_index + 1) {
						RHS.push_back(plus_sign);
						RHS.push_back(input_line[i]);
					}
					else {
						if (input_line[i-1].isOperator == true)
							RHS.push_back(input_line[i-1]);

						RHS.push_back(input_line[i]);
					}
				}
			}
		}

		if (LHS.size() == 0)
			LHS.push_back(zero);

		if (RHS.size() == 0)
			RHS.push_back(zero);

		if (LHS[0].isOperator == true && LHS[0].awperator.compare("+") == 0)
			LHS.erase(LHS.begin());

		if (RHS[0].isOperator == true && RHS[0].awperator.compare("+") == 0)
			RHS.erase(RHS.begin());


		for (int i=0; i<LHS.size(); ++i)
			result.push_back(LHS[i]);

		result.push_back(equal_sign);
		
		for (int i=0; i<RHS.size(); ++i)
			result.push_back(RHS[i]);

		return result;
	}

	vector <Term> shorten_each_side (vector <Term> input_line) 
	{
		int equal_sign_index = 0;
		vector <Term> result, LHS, RHS;
		Term temp, op_t1, op_t2, eql_sign, zero;

		eql_sign.isEqualSign = true;
		eql_sign.awperator = "=";

		zero.isConstant = true;
		zero.co_efficient = 0;

		op_t1.isOperator = true;
		op_t2.isOperator = true;

		for (int i=0; input_line[i].isEqualSign == false; ++i) {
			if (input_line[i].isBrace == false && input_line[i].isOperator == false && input_line[i].isConstant == false) {
				if (temp.isEmpty()) {
					temp = input_line[i];
					
					if (i == 0) 
						op_t1.awperator = "+";
					else 
						if (input_line[i-1].isOperator == true) {
							op_t1.awperator = input_line[i-1].awperator;
						}
				} 
				else {
					if (input_line[i-1].isOperator == true) {
						op_t2.awperator = input_line[i-1].awperator;
					}

					if (op_t1.awperator.compare("-") == 0 && temp.co_efficient > 0) {
						temp.co_efficient *= -1;
					}
					
					if (op_t2.awperator.compare("+") == 0) {
						temp = algebraic_opeartion.add_term(temp, input_line[i]);
					}
					else if (op_t2.awperator.compare("-") == 0)
						temp = algebraic_opeartion.sub_term(temp, input_line[i]);

					if (temp.co_efficient < 0) {
						op_t1.awperator = "-";
						temp.co_efficient *= -1;
					}
					else
						op_t1.awperator = "+";
				}
			}

			++equal_sign_index;
		}

		if (op_t1.awperator.compare("-") == 0)
			LHS.push_back(op_t1);

		if (temp.co_efficient == 0)
			temp = zero;

		LHS.push_back(temp);

		temp.reset();
		op_t1.reset();
		op_t2.reset();

		op_t1.isOperator = true;
		op_t2.isOperator = true;

		for (int i=equal_sign_index+1; i<input_line.size(); ++i) {
			if (input_line[i].isConstant == true) {
				if (temp.isEmpty()) {
					temp = input_line[i];
					
					if (i == 0) 
						op_t1.awperator = "+";
					else 
						if (input_line[i-1].isOperator == true) {
							op_t1.awperator = input_line[i-1].awperator;
						}
				} 
				else {
					if (input_line[i-1].isOperator == true) {
						op_t2.awperator = input_line[i-1].awperator;
					}

					if (op_t1.awperator.compare("-") == 0 && temp.co_efficient > 0) {
						temp.co_efficient *= -1;
					}
					
					if (op_t2.awperator.compare("+") == 0) {
						temp = algebraic_opeartion.add_term(temp, input_line[i]);
					}
					else if (op_t2.awperator.compare("-") == 0)
						temp = algebraic_opeartion.sub_term(temp, input_line[i]);

					if (temp.co_efficient < 0) {
						op_t1.awperator = "-";
						temp.co_efficient *= -1;
					}
					else
						op_t1.awperator = "+";
				}
			}
		}

		if (op_t1.awperator.compare("-") == 0) {
			RHS.push_back(op_t1);
		}

		if (temp.co_efficient == 0)
			temp = zero;
		
		RHS.push_back(temp);

		for (int i=0; i<LHS.size(); ++i)
			result.push_back(LHS[i]);

		result.push_back(eql_sign);

		for (int i=0; i<RHS.size(); ++i) 
			result.push_back(RHS[i]);

		return result;
	}

	string print_line(vector<Term> container)
	{
		string output_line;

		for (int i=0; i<container.size(); ++i) {
			if (container[i].isOperator == true) {
				output_line += container[i].awperator;
				// continue;
			} 
			else if (container[i].isBrace == true) {
				output_line += container[i].brace;
			} 
			else if (container[i].isEqualSign == true) {
				output_line += container[i].awperator;
			}
			else if (container[i].isConstant == true) {
				if (container[i].isFraction == true) {
					output_line += to_string(container[i].co_efficient_fraction[0]);
					output_line += "/";
					output_line += to_string(container[i].co_efficient_fraction[1]);
					output_line += " ";
				}
				else
					output_line += to_string(container[i].co_efficient);
			}
			else {
				if (container[i].co_efficient > 1)
					output_line += to_string(container[i].co_efficient);
				else if (container[i].co_efficient < -1)
					output_line += to_string(container[i].co_efficient);
				else if (container[i].co_efficient == -1)
					output_line += "-";
				else if (container[i].co_efficient == 0)
					output_line += "0";
				else if (container[i].isFraction == true) {
					output_line += to_string(container[i].co_efficient_fraction[0]);
					output_line += "/";
					output_line += to_string(container[i].co_efficient_fraction[1]);
					output_line += " ";
				}

				for (int j=0; j<container[i].get_variable_count(); ++j) {
					output_line += container[i].variable_and_exponent[j].first;

					if (container[i].variable_and_exponent[j].second != 1) {
						output_line += "^";
						output_line += to_string(container[i].variable_and_exponent[j].second);
					}
				}
			}

			output_line += " ";
		}

		return output_line;
	}

	vector <vector <Term>> solve () 
	{
		vector <vector <Term>> whole_process;
		vector <Term> last_processable_line, temp_line;

		Term div_sign, mul_sign, constant;
	
		if (initial_input.size() == 0) {
			cout << "No initial input line given\n";
			return whole_process;
		}

		div_sign.isOperator = true;
		div_sign.awperator = "/";

		mul_sign.isOperator = true;
		mul_sign.awperator = "*";

		whole_process.push_back(initial_input);
		whole_process.push_back(separate_variable_constant(initial_input));

		last_processable_line = shorten_each_side(whole_process[1]);
		whole_process.push_back(shorten_each_side(last_processable_line));

		int flag = -99999, temp_index = 0;
		for (int i=0; i<last_processable_line.size(); ++i) {
			if (last_processable_line[i].isOperator && last_processable_line[i].awperator.compare("-") == 0)
				flag = i;
			else {
				temp_line.push_back(last_processable_line[i]);
				
				if (i == flag + 1 && last_processable_line[i].isEqualSign == false) {
					temp_line[temp_index].co_efficient *= -1;
					flag = -1;
				}				

				++temp_index;
			}
		}

		constant.isConstant = true;
		constant.co_efficient = temp_line[0].co_efficient;

		temp_line[0] = algebraic_opeartion.div_term(temp_line[0], constant);
		temp_line[2] = algebraic_opeartion.div_term(temp_line[2], constant);

		whole_process.push_back(temp_line);

		return whole_process;
	}

	void clear_all()
	{
    	initial_input.clear();
	    parser.clear_all();
	}

};

class Process_Quadratic_Equation
{
private:
    Parser parser;
    Algebraic_Operation algebraic_operation;
    Process_Linear_Expression process_linear_expression;

public:
    vector <Term> initial_equation;
	vector <vector <Term>> factor_eqations;

    void get_input (string str_input) 
    {
		initial_equation.clear();
        parser.take_input(str_input);

        for (int i=0; i<parser.terms.size(); ++i)
            initial_equation.push_back(parser.terms[i]);

	    algebraic_operation.normalize_terms(initial_equation);
    }

    void get_input (vector <Term> vec_input) 
    {
		initial_equation.clear();
        for (int i=0; i<vec_input.size(); ++i)
            initial_equation.push_back(vec_input[i]);

	    algebraic_operation.normalize_terms(initial_equation);
    }

    int find_highest_exponent (vector <Term> input) 
    {
        int highest_exponent = 0;

        algebraic_operation.normalize_terms(input);

        for (int i=0; i<input.size(); ++i) {
            if (input[i].isBrace || input[i].isEqualSign || input[i].isOperator || input[i].isEmpty())
                continue;

            for (int j=0; j<input[i].get_variable_count(); ++j) {
                if (input[i].variable_and_exponent[j].second > highest_exponent)
                    highest_exponent = input[i].variable_and_exponent[j].second;
            }
        }

        return highest_exponent;
    }

	bool isQuadraticEqation () 
	{
		bool returnValue = false;

		if(find_highest_exponent(initial_equation) == 2)
			returnValue = true;

		return returnValue;
	} 

	bool isQuadraticEqation (vector <Term> input) 
	{
		bool returnValue = false;

		if(find_highest_exponent(input) == 2)
			returnValue = true;

		return returnValue;
	}

    Term reverse_operator (Term input)
    {
        Term result;

        if (input.isOperator == true) {

            if (input.awperator.compare("+") == 0) {
                result.isOperator = true;
                result.awperator = "-";
            }
            else if (input.awperator.compare("-") == 0) {
                result.isOperator = true;
                result.awperator = "+";
            }
            else if (input.awperator.compare("*") == 0) {
                result.isOperator = true;
                result.awperator = "/";
            }
            else if (input.awperator.compare("/") == 0) {
                result.isOperator = true;
                result.awperator = "*";
            }
        }

        return result;
    }

    vector <Term> substitution_of_terms (vector <Term> input) 
	{
		vector <Term> final_expression;
		int equal_index = 0;
		bool foundEqualSign = false;
		Term plus_sign, minus_sign, equal_sign, zero;

		plus_sign.isOperator = true;
		plus_sign.awperator = "+";

		minus_sign.isOperator = true;
		minus_sign.awperator = "-";

		equal_sign.isEqualSign = true;
		equal_sign.awperator = "=";

		zero.isConstant = true;
		zero.co_efficient = 0;
		
		for (equal_index=0; input[equal_index].isEqualSign == false; ++equal_index)
			if (input[equal_index].co_efficient != 0)
				final_expression.push_back(input[equal_index]);

		bool passed_operator = false;

		for (int i = equal_index + 1; i<input.size(); ++i) {
			if (input[i].isOperator == true) {
				if (input[i].awperator[0] == '+')
					final_expression.push_back(minus_sign);
				else if (input[i].awperator[0] == '-')
					final_expression.push_back(plus_sign);

				passed_operator = true;
			}
			else if (input[i].co_efficient != 0) {
				if (passed_operator == true) 
					final_expression.push_back(input[i]);
				else {
					final_expression.push_back(minus_sign);
					final_expression.push_back(input[i]);
				}
			}
		}
		
		final_expression.push_back(equal_sign);
		final_expression.push_back(zero);

		return final_expression;
	}

	vector <Term> convert_to_standard_form (vector<Term> input)
	{
		vector <Term> final_expression;

		int highest_power = find_highest_exponent(input);

		bool flag = false;
		Term demo, demo_op, plus_sign, minus_sign, equal_sign, zero;

		plus_sign.isOperator = true;
		plus_sign.awperator = "+";

		minus_sign.isOperator = true;
		minus_sign.awperator = "-";

		equal_sign.isEqualSign = true;
		equal_sign.awperator = "=";

		zero.isConstant = true;
		zero.co_efficient = 0;

		while (highest_power > -1) 
		{
			if (highest_power > 0) 
			{
				for (int i=0; input[i].isEqualSign == false; ++i) {
					if(!input[i].isConstant && !input[i].isBrace && !input[i].isOperator && input[i].variable_and_exponent[0].second == highest_power) {
						if (!flag) {
							demo = input[i];
							if (i == 0)	demo_op = plus_sign;
							else demo_op = input[i-1];
							flag = true;
						}
						else {
							if (demo_op.awperator[0] == input[i-1].awperator[0]) {
								demo = algebraic_operation.add_term(demo, input[i]);
								demo_op = input[i-1];
							}
							else {
								if (demo.co_efficient > input[i].co_efficient) 
									demo = algebraic_operation.sub_term(demo, input[i]);
								else {
									demo = algebraic_operation.sub_term(input[i], demo);
									demo_op = input[i-1];
								}
							}
						}
					}
				} 
			}

			else {
				for (int i=0; i<input.size(); ++i) {
					if (input[i].isConstant == true) {
						if (!flag) {
							demo = input[i];
							if (i == 0) demo_op = plus_sign;
							else demo_op = input[i-1];
							flag = true;
						}
						else {
							if (demo_op.awperator[0] == input[i-1].awperator[0]) {
								demo = algebraic_operation.add_term(demo, input[i]);
								demo_op = input[i-1];
							}
							else {
								if (demo.co_efficient > input[i].co_efficient) 
									demo = algebraic_operation.sub_term(demo, input[i]);
								else {
									demo = algebraic_operation.sub_term(input[i], demo);
									demo_op = input[i-1];
								}
							}
						}
					}
				}

			}

			if (!demo.isEmpty() && !demo_op.isEmpty() && demo.co_efficient != 0){
				final_expression.push_back (demo_op);
				final_expression.push_back (demo);
			}

			demo.reset();
			demo_op.reset();
			flag = false;

			--highest_power;
		}

		if (final_expression[0].isOperator == true && final_expression[0].awperator[0] == '+')
			final_expression.erase(final_expression.begin() + 0);

		final_expression.push_back (equal_sign);
		final_expression.push_back (zero);

		return final_expression;
	}

	int cheak_for_integer_root (vector <Term> input) 
	{
		int has_integer_root = -1;
		
		int a = 0, b = 0, c = 0;

		for (int i=0; input[i].isEqualSign == false; ++i) {
			if (!input[i].isOperator && !input[i].isBrace) {
				if (input[i].isConstant == true){
					c = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	c *= -1;
				}
				else if (input[i].variable_and_exponent[0].second == 1) {
					b = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	b *= -1;
				}
				else if (input[i].variable_and_exponent[0].second == 2) {
					a = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	a *= -1;
				}
			}
		}

		int discriminant = b*b - 4*a*c, temp;
		
		if (discriminant < 0.0)
			return has_integer_root;
		else
			has_integer_root = 0;

		double cheak = 0.0;

		if (discriminant >= 0) {
			temp = sqrt(discriminant);
			cheak = sqrt(discriminant);
			
			cheak -= (double)temp;
		
			if (cheak == 0.0) {
				has_integer_root = 1;
				// cout << "found one";
			}
		}
		
		return has_integer_root;
	}

	pair <int, int> find_int_root (vector <Term> input) 
	{
		if (cheak_for_integer_root(input) < 1)
			return find_real_root(input);
		
		int a = 0, b = 0, c = 0;
		pair <int, int> root;

		for (int i=0; input[i].isEqualSign == false; ++i) {
			if (!input[i].isOperator && !input[i].isBrace) {
				if (input[i].isConstant == true){
					c = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	c *= -1;
				}
				else if (input[i].variable_and_exponent[0].second == 1) {
					b = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	b *= -1;
				}
				else if (input[i].variable_and_exponent[0].second == 2) {
					a = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	a *= -1;
				}
			}
		}

		double t1 = (-b + sqrt(b*b - 4*a*c))/(2*a), t2 = (-b - sqrt(b*b - 4*a*c))/(2*a);

		int temp = (-b + sqrt(b*b - 4*a*c))/(2*a);
		if ((t1 - (double)temp) == 0.0)
			root.first = t1;
		else
			root.first = t2;
			
		temp = (-b - sqrt(b*b - 4*a*c))/(2*a);
		root.second = temp;

		return root;
	}

	pair <double, double> find_real_root (vector <Term> input) 
	{
		if (cheak_for_integer_root(input) < 0)
			return make_pair(INT_MIN, INT_MIN);
		
		int a = 0, b = 0, c = 0;
		pair <double, double> root;

		for (int i=0; input[i].isEqualSign == false; ++i) {
			if (!input[i].isOperator && !input[i].isBrace) {
				if (input[i].isConstant == true){
					c = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	c *= -1;
				}
				else if (input[i].variable_and_exponent[0].second == 1) {
					b = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	b *= -1;
				}
				else if (input[i].variable_and_exponent[0].second == 2) {
					a = input[i].co_efficient;
					if (i > 0 && input[i-1].awperator[0] == '-')	a *= -1;
				}
			}
		}

		double temp = (-b + sqrt(b*b - 4*a*c))/(2*a);
		root.first = temp;

		temp = (-b - sqrt(b*b - 4*a*c))/(2*a);
		root.second = temp;

		return root;
	}

	vector <vector <Term>> remainder_theorum (vector <Term> input) 
	{
		vector <vector <Term>> returnVal;
		pair <int, int> root = find_int_root (input);

		// creating initial factor
		vector <Term> factor, allFacotors;
		Term demo;
		
		demo.reset();
		demo.co_efficient = 1;
		{
			string str;
			if (!input[0].isOperator)	str = input[0].variable_and_exponent[0].first;
			else if (!input[1].isOperator)	str = input[1].variable_and_exponent[0].first;
			demo.variable_and_exponent.push_back(make_pair(str, 1));
		}

		factor.push_back(demo);
		demo.reset();

		demo.isOperator = true;
		
		if (root.first > 0) 
			demo.awperator = "-";
		else if (root.first < 0)
			demo.awperator = "+";

		if (root.first != 0)	
			factor.push_back(demo);

		demo.reset();

		if (root.first != 0) {
			demo.isConstant = true;
			demo.co_efficient = abs(root.first);
			demo.co_efficient_fraction[0] = 1; demo.co_efficient_fraction[1] = 1;
			factor.push_back(demo);
			demo.reset();
		}
		// initial factor x +/- a created

		vector <Term> temp_line;
		returnVal.push_back(temp_line);
		returnVal.push_back(temp_line);

		Term op_brace, cls_brace, equal_sign, zero;
		Term demo_op;

		op_brace.isBrace = true;
		op_brace.brace = "(";

		cls_brace.isBrace = true;
		cls_brace.brace = ")";

		equal_sign.isEqualSign = true;
		equal_sign.awperator = "=";

		zero.isConstant = true;
		zero.co_efficient = 0;

		int j = -1;
		demo.reset();
		demo_op.reset();

		for (int i=0; input[i].isEqualSign == false; ++i) 
		{
			if (!input[i].isOperator && !input[i].isBrace) {
				if (i == 0 || i == 1){
					if (i > 0)
						demo_op = input[i-1];			
					demo = input[i];
				}
				else {
					int diff, n1, n2;

					if (algebraic_operation.is_operable(demo, input[i]) != 1 && algebraic_operation.is_operable(demo, input[i]) != 2)
						n1 = 0;
					else if (input[i-1].isOperator && input[i-1].awperator[0] == '-') 
						n1 = -1 * input[i].co_efficient;
					else n1 = abs(input[i].co_efficient);

					if (demo_op.isOperator && demo_op.awperator[0] == '-')
						n2 = -1 * demo.co_efficient;
					else n2 = abs(demo.co_efficient);

					diff = n1 - n2;

					if (diff > 0) {
						demo_op.isOperator = true;
						demo_op.awperator = "+";
					} else if (diff < 0) {
						demo_op.isOperator = true;
						demo_op.awperator = "-";
					} else break;
					demo.co_efficient = abs(diff);
				}
				
				// first entry 
				if (demo_op.isOperator) { 
					returnVal[0].push_back(demo_op);	++j; 
					returnVal[1].push_back(demo_op);
				}

				returnVal[0].push_back(demo);	++j;

				if (demo.variable_and_exponent[0].second > 1) 
					demo.variable_and_exponent[0].second -= 1;
				else if (demo.variable_and_exponent[0].second == 1) {
					demo.isConstant = true;
					demo.variable_and_exponent.clear();
				}
				returnVal[1].push_back(demo);

				returnVal[1].push_back(op_brace);
				for(int k=0; k<factor.size(); ++k)
					returnVal[1].push_back(factor[k]);
				returnVal[1].push_back(cls_brace);

				if (demo_op.isOperator) 	demo_op = algebraic_operation.multiply_operator(demo_op, factor[1]);
				else 	demo_op = factor[1];
				returnVal[0].push_back(demo_op); 	++j;

				demo = algebraic_operation.mul_term(demo, factor[2]);
				returnVal[0].push_back(demo);	++j;
			}
		}

		returnVal[0].push_back(equal_sign);
		returnVal[0].push_back(zero);

		returnVal[1].push_back(equal_sign);
		returnVal[1].push_back(zero);

		// final factorized line
		temp_line.push_back(op_brace);
		bool shouuld_take = true;
		for (int i=0; returnVal[1][i].isEqualSign == false; ++i) {
			if (returnVal[1][i].isBrace && returnVal[1][i].brace[0] == '(') 
				shouuld_take = false;

			if (shouuld_take) {
				temp_line.push_back(returnVal[1][i]);
			} else {
				if (returnVal[1][i].isBrace && returnVal[1][i].brace[0] == ')')
					shouuld_take = true;
			}
		} temp_line.push_back(cls_brace);

		temp_line.push_back(op_brace);
		for (int i=0; i<factor.size(); ++i)
			temp_line.push_back(factor[i]);
		temp_line.push_back(cls_brace);

		temp_line.push_back(equal_sign);
		temp_line.push_back(zero);
		returnVal.push_back(temp_line);

		return returnVal;
	}

	void extract_factor_equation (vector <Term> input) 
	{
		vector <Term> temp_line;
		Term equal_sign, zero;

		equal_sign.isEqualSign = true;
		equal_sign.awperator = "=";

		zero.isConstant = true;
		zero.co_efficient = 0;

		bool should_take = false;
		for (int i=0; input[i].isEqualSign == false; ++i) {
			if (input[i].isBrace && input[i].brace[0] == '(') {
				should_take = true;
				continue;
			}

			if (should_take) {
				if (input[i].isBrace && input[i].brace[0] == ')') {
					should_take = false;

					temp_line.push_back(equal_sign);
					temp_line.push_back(zero);

					factor_eqations.push_back(temp_line);
					temp_line.clear();
				}
				else 
					temp_line.push_back(input[i]);
			}
		}
	}

	vector <vector <Term>> solve () 
	{
		vector <vector <Term>> whole_process, temp_process_container;
		vector <Term> last_processed_line, temp_line, end_line;

		last_processed_line.assign(initial_equation.begin(), initial_equation.end());
		whole_process.push_back(last_processed_line);

		temp_line.clear();
		temp_line = substitution_of_terms(last_processed_line);

		if (!algebraic_operation.compare_line(temp_line, last_processed_line)){
			last_processed_line.clear();
			last_processed_line = temp_line;
			whole_process.push_back(temp_line);
		}

		temp_line.clear();
		temp_line = convert_to_standard_form(last_processed_line);
		
		if (!algebraic_operation.compare_line(temp_line, last_processed_line)){
			last_processed_line.clear();
			last_processed_line = temp_line;
			whole_process.push_back(temp_line);
		}

		if (isQuadraticEqation(last_processed_line) == false) {
			process_linear_expression.get_input(last_processed_line);

			temp_process_container.clear();
			temp_process_container = process_linear_expression.solve();

			whole_process.insert(whole_process.end(), temp_process_container.begin(), temp_process_container.end());

			return whole_process;
		}

		if (cheak_for_integer_root(last_processed_line) < 1) 
		{
			if (cheak_for_integer_root(last_processed_line) == 0) {
				Term var_x, const_val, equal_sign;
				pair <double, double> real_root = find_real_root(last_processed_line);

				var_x.co_efficient = 1;
				for (int i=0; i<last_processed_line.size(); ++i)
					if (!last_processed_line[i].isBrace && !last_processed_line[i].isOperator && !last_processed_line[i].isEqualSign && !last_processed_line[i].isConstant) {
						var_x.variable_and_exponent.push_back(make_pair(last_processed_line[i].variable_and_exponent[0].first, 1));
						break;
					} 

				equal_sign.isOperator = true;
				equal_sign.awperator = "=";

				const_val.hasHardVal = true;
				const_val.hard_value = real_root.first;

				temp_line.clear();
				temp_line.push_back(var_x);
				temp_line.push_back(equal_sign);
				temp_line.push_back(const_val);

				whole_process.push_back(temp_line);

				temp_line.clear();
				const_val.hard_value = real_root.second;

				temp_line.push_back(var_x);
				temp_line.push_back(equal_sign);
				temp_line.push_back(const_val);

				whole_process.push_back(temp_line);
			}

			return whole_process;
		}

		temp_process_container = remainder_theorum(last_processed_line);
		for (int i=0; i<temp_process_container.size();  ++i)
			whole_process.push_back(temp_process_container[i]);

		last_processed_line = whole_process[whole_process.size()-1];
		extract_factor_equation(last_processed_line);

		Term end_sign;
		end_sign.isEqualSign = true;
		end_sign.awperator = "#";
		end_line.push_back(end_sign);

		for (int i=0; i<factor_eqations.size(); ++i) {
			process_linear_expression.get_input(factor_eqations[i]);

			temp_process_container.clear();
			temp_process_container = process_linear_expression.solve();

			whole_process.push_back(end_line);
			whole_process.insert(whole_process.end(), temp_process_container.begin(), temp_process_container.end());
		}

		return whole_process;
	}

	void clear_all()
	{
 		parser.clear_all();
    	process_linear_expression.clear_all();

    	initial_equation.clear();
    	factor_eqations.clear();
	}
        
};

class Driver_class
{
private:
    /* data */ 

public:

    Driver_class(/* args */) {} 
    ~Driver_class() {}

	string print_line(vector<Term> container)
	{
		string output_line;

		for (int i=0; i<container.size(); ++i) {
			if (container[i].isOperator == true) {
				output_line += container[i].awperator;
				// continue;
			} 
			else if (container[i].isBrace == true) {
				output_line += container[i].brace;
			} 
			else if (container[i].isEqualSign == true) {
				output_line += container[i].awperator;
			}
			else if (container[i].isConstant == true) {
				if (container[i].isFraction == true) {
					output_line += to_string(container[i].co_efficient_fraction[0]);
					output_line += "/";
					output_line += to_string(container[i].co_efficient_fraction[1]);
					output_line += " ";
				}
				else
					output_line += to_string(container[i].co_efficient);
			}
			else if (container[i].hasHardVal == true) {
				output_line += to_string(container[i].hard_value);
			}
			else {
				if (container[i].co_efficient > 1)
					output_line += to_string(container[i].co_efficient);
				else if (container[i].co_efficient < -1)
					output_line += to_string(container[i].co_efficient);
				else if (container[i].co_efficient == -1)
					output_line += "-";
				else if (container[i].co_efficient == 0)
					output_line += "0";
				else if (container[i].isFraction == true) {
					output_line += to_string(container[i].co_efficient_fraction[0]);
					output_line += "/";
					output_line += to_string(container[i].co_efficient_fraction[1]);
					output_line += " ";
				}

				for (int j=0; j<container[i].get_variable_count(); ++j) {
					output_line += container[i].variable_and_exponent[j].first;

					if (container[i].variable_and_exponent[j].second != 1) {
						output_line += "^";
						output_line += to_string(container[i].variable_and_exponent[j].second);
					}
				}
			}

			output_line += " ";
		}

		return output_line;
	}

	double calculate_term(Term term, double val_x)
	{
    	double val_y = 0.0, temp = 1;

    	if (!term.isBrace && !term.isOperator && !term.isEqualSign)
    	{
        	if (term.isFraction)    val_y = (double)term.co_efficient_fraction[0] / (double)term.co_efficient_fraction[1];
        	else val_y = term.co_efficient;

        	if (!term.isConstant) {
            	for (int i=0; i<term.get_variable_count(); ++i) {
                	for (int j=0; j<term.variable_and_exponent[i].second; ++j)
                    	temp *= val_x;
            	}

            	val_y *= temp;
        	}
    	}

    	return val_y;
	}

    void start ()
    {
		Tokenizer t1;
    	Parser p1;
    	Algebraic_Operation alg1;
		Process_Linear_Expression lexp1;
		Process_Quadratic_Equation qexp1;

        /* Taking input form the user */
        
        string inpt;
        getline(cin, inpt, '\n');

        /* declaring utility objet */       

        p1.take_input(inpt);
        p1.test_parse_term();

		// alg1.normalize_terms(p1.terms);
		alg1.normalize_terms(p1.terms);
		// alg1.shroten_terms(p1.terms[0]);

		cout << "after sorting\n";
		p1.test_parse_term();

		string out = print_line(p1.terms);
		cout << endl << out << endl;
    
		vector <Term> testing_container;
		vector <vector <Term>> process_container;
		lexp1.get_input(inpt);

		// out = print_line(lexp1.initial_input);
		// cout << out << endl;

		testing_container = lexp1.separate_variable_constant(lexp1.initial_input);

		out = print_line(testing_container);
		cout << out << endl;
		//print_line(testing_container);

		out = print_line(lexp1.shorten_each_side(testing_container));
		cout << out << endl;

		p1.test_term_container(lexp1.shorten_each_side(testing_container));

		process_container = lexp1.solve();
		for (int i=0; i<process_container.size(); ++i) {
			out = print_line(process_container[i]);
			cout << out << endl;
		}

		cout << "input a quadratic eqation\n";
		getline(cin, inpt, '\n');

		qexp1.get_input(inpt);
		process_container.clear();
		process_container = qexp1.solve();

		bool temp_flag = true;
		out = "";
		for (int i=0; i<process_container.size(); ++i) {
			if (process_container[i][0].isEqualSign && process_container[i][0].awperator[0] == '#') {
				out += "\n\n";
				if (temp_flag) { out += "If,\n";	temp_flag=false; }
				else			 out += "Again,\n";
				continue;
			}
			out += print_line(process_container[i]);
			out += '\n';
		} cout << out;

		testing_container.clear();

		qexp1.clear_all();
		qexp1.get_input(inpt);
		testing_container = qexp1.substitution_of_terms(qexp1.initial_equation);
		testing_container = qexp1.convert_to_standard_form(testing_container);

		out = print_line(testing_container);
		cout << out;
	}


};
































































































































int main(void)
{
	
	Driver_class driver;

    driver.start();

	return 0;
}
