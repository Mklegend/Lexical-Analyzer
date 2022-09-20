#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	ERROR,
	Identifier,
	Variable,
	Number,
	Letter,
	String,
	Comment,
	AssignmentOperator,
	RelationalOperator,
	ArithematicOperator,
	BlockStart,
	BlockEnd,
	SpecialCharacter,
	Function,
	If,
	Else,
	Int,
	Do,
	Until,
	Then,
	Read,
	Display,
	DisplayLine,
	Return
};
//structure of a token 
struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme, TokenType tokenType);
	//constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  //used for storing file sample_code.ol content
	vector<token> tokens; //vector to store all (tokens,lexeme) pairs
	void Tokenize();//populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();//just print everything as it is present in file
	token getNextToken();//get next token
	void resetPointer();//reset pointer to start getting tokens from start
	int getCurrentPointer();//get where current pointer in tokens vector is
	void setCurrentPointer(int pos);//move current pointer to wherever
	token peek(int);//peek the next token
	
	// Helper Functions
	bool isLetter(char);
	bool isSpecialCharacter(char);


	// Functions for DFAs
	void identifierDFA(int&); // Checks for Identifier Given the Position of the Pointer
	void keywordDFA(int&); // Checks for Keyword Given the Position of the Pointer
	void relationalOperatorDFA(int&); // Checks for Relational Operator Given the Position of the Pointer
};

#endif // !_LEXER_H
