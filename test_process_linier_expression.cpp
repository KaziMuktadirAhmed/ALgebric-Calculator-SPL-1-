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

    int co_efficient = 1;
	int co_efficient_fraction[2];

    vector< pair <string, int> > variable_and_exponent;

	int get_variable_count() 
	{
		return variable_and_exponent.size();
	}

	bool isEmpty()
	{
		if (isEqualSign == false && isOperator == false && isBrace == false && isConstant == false)
			if (variable_and_exponent.size() == 0)
				return true;

		return false; 	
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
		
		//tokenized_input.testTokenizer();

        // Term temp, temp1;
		// temp = get_term(tokenized_input.tokens.size());

		// cout << temp.co_efficient << " ";
		// for(int i=0; i<temp.variable_and_exponent.size(); ++i)
		// 	cout << temp.variable_and_exponent[i].first << "^" << temp.variable_and_exponent[i].second << " "; 
		// cout << endl; 

		// temp1 = get_term(tokenized_input.tokens.size());
		// if (temp1.isOperator)
		// 	cout << temp1.awperator << endl;
		// else if (temp1.isBrace)
		// 	cout << temp1.brace << endl;
		// else if (temp1.isEqualSign)
		// 	cout << temp1.awperator << endl;
		
		parse_term();
		//test_parse_term();
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

class Algebraic_Opeartion
{
private:

public:
	Algebraic_Opeartion(/* args */) {}
	~Algebraic_Opeartion() {}

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
		
		if (comparator_value > -1) {
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

		if (comparator_value > -1) {

			if(A.co_efficient % B.co_efficient != 0) {

				temp_fraction[0] = A.co_efficient;
				temp_fraction[1] = B.co_efficient;

				reduce_fraction.start(temp_fraction);

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


	// Normalizing utility functions

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

class Process_Linier_Expression
{
private:
    /* data */
    vector <Term> initial_input;

    // Utility functions //
    Parser parser;
    Algebraic_Opeartion algebraic_opeartion;

public:
    Process_Linier_Expression(/* args */) {}
    ~Process_Linier_Expression() {}

    void get_input (string str_input) 
    {
        parser.take_input(str_input);

        for (int i=0; i<parser.terms.size(); ++i)
            initial_input.push_back(parser.terms[i]);
    }

    void get_input (vector <Term> vec_input) 
    {
        for (int i=0; i<vec_input.size(); ++i)
            initial_input.push_back(vec_input[i]);
    }

    Term reverse_operator (Term input)
    {
        Term result;

        if (input.isOperator == true) {

            if (input.awperator.compare("+")) {
                result.isOperator = true;
                result.awperator = "-";
            }
            else if (input.awperator.compare("-")) {
                result.isOperator = true;
                result.awperator = "+";
            }
            else if (input.awperator.compare("*")) {
                result.isOperator = true;
                result.awperator = "/";
            }
            else if (input.awperator.compare("/")) {
                result.isOperator = true;
                result.awperator = "*";
            }
        }

        return result;
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
				output_line += to_string(container[i].co_efficient);
			}
			else {
				if (container[i].co_efficient > 1)
					output_line += to_string(container[i].co_efficient);
				else if (container[i].co_efficient < -1)
					output_line += to_string(container[i].co_efficient);
				else if (container[i].co_efficient == -1)
					output_line += "-";
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

    void start ()
    {
		Tokenizer t1;
    	Parser p1;
    	Algebraic_Opeartion alg1;

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
    
		vector <Term> testing_container_for_add;
		testing_container_for_add.push_back(alg1.div_term(p1.terms[0], p1.terms[2]));

		out = print_line(testing_container_for_add);
		cout << endl << out << endl;
	}

};
































































































































int main(void)
{
	
	Driver_class driver;

    driver.start();

	return 0;
}
