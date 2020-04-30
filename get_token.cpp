#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER 1
#define VARIABlE  2
#define NUMBER    3

char *prog; /* points to the expression to be analyzed */
char input[100];
char token[100];
int token_type;

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
	if(strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0)
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

	if(!*prog) return; // at the end of expression

	while(isspace(*prog)) ++prog; // skip over the white space

	if(strchr("+-*/%^=()", *prog)) {
		token_type = DELIMITER;
		// advance to next char
		*temp++ = *prog++;
	}
	else if(is_alphabte(*prog)) {
		while(!is_delimiter(*prog) && !is_digit(*prog) && !isspace(*prog)) *temp++ = *prog++;
		token_type = VARIABlE;
	}
	else if(is_digit(*prog)) {
		while(!is_delimiter(*prog) && !is_alphabte(*prog) && !isspace(*prog)) *temp++ = *prog++;
		token_type = NUMBER;
	}

	*temp = '\0';
}

int main(void)
{
	fgets(input,100,stdin);
	prog = input;

	while(1){
		if((prog - input) >= strlen(input)) break;
		get_token();

		// print the output
		printf("%s\t",token);

		if(token_type == DELIMITER)
			printf("This token is an oparator or braces\n");
		else if(token_type == VARIABlE)
			printf("This token is a variable\n");
		else if(token_type == NUMBER)
			printf("This token is  a number\n");
	}

	return 0;
}