#include "Tokenizer.h"

bool Tokenizer::is_alphabte(int str)
{
    if((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
        return true;
    else
        return false;
}

bool Tokenizer::is_digit(int str)
{
    if(str >= '0' && str <= '9')
        return true;
    else
        return false;
}

bool Tokenizer::is_delimiter(char c)
{
    if(strchr(" +-/*%^=(){}[]", c) || c == 9 || c == '\r' || c == 0 || c == '\n')
        return true;
    else
        return false;
}

void Tokenizer::get_token()
{
            char *temp;
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

void Tokenizer::tokenize_input(string inpt)
{
            strcpy(input, inpt.c_str());
            prog = input;

            while(1){
                if((prog - input) >= (int)strlen(input))
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

Tokenizer::Tokenizer()
{

}

void Tokenizer::start(string user_input)
{
    tokenize_input(user_input);
}

int Tokenizer::get_token_count()
{
    return types.size();
}

void Tokenizer::testTokenizer()
{
    if (types.size() == 0){
        cout << "No input given to the Tokenizer.\n";
        return;
    }

    for(int i=0; i<(int)tokens.size(); ++i)
    {
        if(types[i] == OPERATOR)      cout << "It's Operator \t";
        else if (types[i] == VARIABLE) cout << "It's Variable \t";
        else if (types[i] == NUMBER)   cout << "It's Number \t";
        else if (types[i] == BRACES)   cout << "It's Braces \t";
        else if (types[i] == EQUAL_SIGN)   cout << "It's Equal_sign \t";
        else if (types[i] == EXPONENT_SIGN)   cout << "It's Exponent_sign \t";

        cout << "token : " << tokens[i] << "\n";
    }
}

void Tokenizer::clear_data()
{
    tokens.clear();
    types.clear();
}
