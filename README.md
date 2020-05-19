# ALgebric-Calculator-SPL-1-

 1st goal: linier equation solver using prefix and postfix notation 
 
 steps:
 1) define basic arithmatic procedure.
          Example: converting conjugate root, reducing fractoin, GCD and LCM.
 2) create a integer parser to separate integer from string input.
          Example: parseFraction(string inpt) in reducing fraction, simple integer parser.
 3) create a user interface for input and output. maybe a notepad or any type of text editor.
 
NOTE : for some reason using getline to input the string results in a bug not containing the constant value after the equal sign. Used fgets to read the string input instead of getline.

NOTE : the new eqaution solver uses the recursive decent parser as it's parsing function. it's more accurate then the custom made parser the preveious one used. both of the function can only solve single variable linear eqn. the recursive decent parser can parse every kind of algebraic expression. the separate term function should be diffrent for linear and non linear expression. the given one is only applicable for linear expression.
