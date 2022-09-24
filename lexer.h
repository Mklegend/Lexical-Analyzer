#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//all your tokens goes here
enum TokenType
{
	END_OF_FILE = 0,
	ERROR = 1,
	Identifier = 2,
	Variable = 3,
	Number = 4,
	Letter = 5,
	String = 6,
	Comment = 7,
	AssignmentOperator = 8,
	RelationalOperator = 9,
	ArithematicOperator = 10,
	BlockStart = 11,
	BlockEnd = 12,
	SpecialCharacter = 13,
	Function = 14,
	If = 15,
	Else = 16,
	Int = 17,
	Do = 18,
	Until = 19,
	Then = 20,
	Read = 21,
	Display = 22,
	DisplayLine = 23,
	Return = 24,
	Comma = 25,
	Collon = 26,
	SemiCollan = 27,
	Dollar = 28,
	OpenParenthesis = 29,
	CloseParenthesis = 30,
	Plus = 31,
	Minus = 32,
	Multiply = 33,
	Divide = 34,
	Modulus = 35,
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
	bool isArithematicOperator(char);
	bool isNumber(char);
	bool isKeyword(string str);
	bool isRelationalOperator(string str);

	// Functions for DFAs
	void identifierDFA(vector<char>::iterator &pointer); // Checks for Identifier Given the Position of the Pointer
	void keywordDFA(vector<char>::iterator &pointer); // Checks for Keyword Given the Position of the Pointer
	void relationalOperatorDFA(vector<char>::iterator &pointer); // Checks for Relational Operator Given the Position of the Pointer
	void specialCharacterDFA(vector<char>::iterator &pointer); 
	void arithematicOperatorDFA(vector<char>::iterator &pointer); // Checks for Arithematic Operator Given the Position of the Pointer
	void variableDFA(vector<char>::iterator &pointer);
	void commentDFA(vector<char>::iterator &pointer);
	void stringDFASingleQuote(vector<char>::iterator &pointer);
	void stringDFADoubleQuote(vector<char>::iterator &pointer);
	void assignmentOperator(vector<char>::iterator &pointer);
	void startingBlockDFA(vector<char>::iterator &pointer);
	void closingBlockDFA(vector<char>::iterator &pointer);
	void numberDFA(vector<char>::iterator &pointer);
};

#endif // !_LEXER_H
