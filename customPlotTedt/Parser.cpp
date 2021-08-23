#include "Parser.h"

Parser::Parser()
{

}

// Utility functions

int Parser::token_to_int(string temp)
{
    int toNum = 0;

    for	(int i=0; temp[i] != '\0'; ++i)
        toNum = toNum*10 + (temp[i]-'0');

    return toNum;
}

void Parser::clear_pair(pair<char, int> &pr)
{
    pr.first = '\0';
    pr.second = 0;
}

void Parser::test_parse_term()
{
    for(int i=0; i<(int)terms.size(); ++i) {
        if (terms[i].isOperator)
            cout << terms[i].awperator << endl;
        else if (terms[i].isBrace)
            cout << terms[i].brace << endl;
        else if (terms[i].isEqualSign)
            cout << terms[i].awperator << endl;
        else if (terms[i].isConstant)
            cout << terms[i].co_efficient << endl;
        else {
            cout << terms[i].co_efficient << "  ";

            for(int j=0; j<terms[i].get_variable_count(); ++j) {
                cout << terms[i].variable_and_exponent[j].first << "^" << terms[i].variable_and_exponent[j].second << " ";
            } cout << endl;
        }
    }
}

void Parser::test_term_container(vector<Term> terms)
{
    for(size_t i=0; i<terms.size(); ++i) {
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

// Parsing Functions

Term Parser::get_term(int token_count)
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

void Parser::parse_term()
{
    Term demo;
    int token_count = tokenized_input.get_token_count();

    start_index = 0;

    while (start_index < token_count) {
        demo = get_term(token_count);
        terms.push_back(demo);
    }
}

// User Interface part

void Parser::take_input(string user_input)
{
    Term temp, temp1;

    tokenized_input.start(user_input);
    tokenized_input.testTokenizer();
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
    test_parse_term();
}
