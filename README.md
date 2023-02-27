# CPSC 323 Project
## Assignment 1: The Lexer

1. Problem Statement:
This lexer reads in a file containing the source code of Rat23S to generate tokens and write out the results to an output file.
2. How to use your program:

3. Design of your program:
Our program consists of 7 token types which are IDENTIFIER, INTEGER, REAL, KEYWORD, OPERATOR, SEPARATOR, and INVALID all of enum type. We use an unordered set of string type to store the finite token types keywords, operators, and separators. Using a struct, we designate it Token and create objects ‘type’ of TokenType and ‘lexeme’ of string type. Since there are a finite amount of operators, keywords, and separators, we can pull from the unordered sets and compare but since there can be an infinite amount of integers, reals, and identifiers we needed to create DFSMS. Each of the 3 tokens have their own DFSM for a total of 3 DFSMS. The integer DFSM has 4 states. State 0 is the starting state and states 2 and 3 are accepting states. The real DFSM has 5 states since it takes into account the decimal. For this DFSM, the starting state is 0 and the accepting state is 4. For identifiers, the DFSM has 3 states that account for letters, digits, and “_”. The starting state is 0 and the accepting state is 2. In order to generate tokens, we created a tokenize function which takes an input file as a parameter and reads through each line using a while loop. The tokenize function will read through each line and first ignore all comments which start with [* until the tokenize function reads *]. Then the line received from getline will be separated by white spaces and the string will be iterated through character by character searching for separators and operators since they do not require any spaces. The iterator will keep adding characters to each other to create a string which will then be checked to see if the resulting string is an integer, real, identifier, keyword, or invalid. If there is a separator or operator, the function will separate the previous token from the separator or operator because they are separate tokens. Each token will then be pushed onto a vector named tokens using push_back(). In our results function, we use iterators to iterate through the vector and output each token and its respective lexeme.
5. Any Limitation:
N/A
5. Any shortcomings:
N/A
