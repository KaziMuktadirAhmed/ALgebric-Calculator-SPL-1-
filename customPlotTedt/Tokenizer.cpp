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
                if((prog - input) >= strlen(input))
                    break;

                get_token();

                string demo;
                demo.assign(token);

                if(token_type >= 1 && token_type <= 3){
                    tokens.push_back(demo);
                    types.push_back(token_type);
                }
            }

            // tesing part //
//             for(unsigned int i=0; i<tokens.size(); ++i)
//             {
//                if(types[i] == DELIMITER)      cout << "It's Delimeter \t";
//                else if (types[i] == VARIABLE) cout << "It's Variable \t";
//                else if (types[i] == NUMBER)   cout << "It's Number \t";

//                cout << "token : " << tokens[i] << "\n";
//             }
            // end of testing part //
}

Tokenizer::Tokenizer()
{

}

void Tokenizer::start(string user_input)
{
    tokenize_input(user_input);
}

void Tokenizer::testTokenizer()
{
            if (types.size() == 0){
                cout << "No input given to the Tokenizer.\n";
                return;
            }

            for(unsigned int i=0; i<tokens.size(); ++i)
            {
                if(types[i] == DELIMITER)      cout << "It's Delimeter \t";
                else if (types[i] == VARIABLE) cout << "It's Variable \t";
                else if (types[i] == NUMBER)   cout << "It's Number \t";

                cout << "token : " << tokens[i] << "\n";
            }
}

void Tokenizer::clear_data()
{
    tokens.clear();
    types.clear();
}
