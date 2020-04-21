# ALgebric-Calculator-SPL-1-

 This branch is alternative parsing section which uses resource from "C The Complete reference - Chapter 24 - Expression parsing      and Evaluation"
 
 get_token(): 
 The function can be used to parse any expression string. The function separates a string into 3 types of token

       1. NUMBER - are considered the digits and  numerical values in the expression string
       2. VARIABLES - any type of alphabatic charecter is considered as VRIABLE type token in this function
       3. DELIMITER - are considered as operators or braces in a expression.
 
 1. The get_token() need a delimeter to set diffence from one token type to another. 
 2. The delimiter considered in this function are ' ', +, -, /, *, %, ^, (, ), = 
 3. The function will not separate a text 555x into 555 and x beacuse there is no delimeter between them 
 4. But it will separte 555*x or 555 x into 555 and x
