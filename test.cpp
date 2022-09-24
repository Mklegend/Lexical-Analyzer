#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <vector>

using namespace std;

enum types{Type1,Type2};


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

struct token
{
	string lexeme;
	TokenType tokenType;//enum type
	//constructor
	token(string lexeme_, TokenType tokenType_){
        lexeme = lexeme_;
        tokenType = tokenType_;
    }
	//constructor default
	token(){
        lexeme = "";
    }
	void Print(){
        cout<<"("<<" "<<tokenType<<", "<<lexeme<<")"<<endl;
    }
};

vector<string> names;
vector<token> tokens;


void print(vector<string>::iterator &it){
    while(it!=names.end()){
        cout<<*it<<endl;
        it++;
    }
}



bool isLetter(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? true : false;
}
bool isSpecialCharacter(char ch)
{
    return (ch == ':' || ch == ';' || ch == ',' || ch == '$' || ch == '(' || ch == ')') ? true : false;
}
bool isArithematicOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') ? true : false;
}
bool isNumber(char ch){
    return (ch>='0' && ch<='9') ? true : false;
}

bool isKeyword(string str){
    return (str == "function" || str == "if" || str == "else" || str == "int" || str == "then" || str == "do" 
    || str == "while" || str == "display" || str == "displayline" || str == "read" || str == "return") ? true : false;
}

bool isRelationalOperator(string str){
    return (str == "-lt" || str == "-gt" || str == "-eq" || str == "-le" || str == "-ge") ? true : false; 
}

void identifierDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    token_.tokenType = TokenType::Identifier;
    // If Reads Letter or UnderScore at State 0 transition to State 1
    // Else Transition to State -1 Which is a Discarded State
    while (!terminated)
    {
        // If Space is Encountered at State 1 Transition to State 2 else Stay on the same State
        // Note : handle cases of special characters appearing instead of Space !
        state = ((isLetter(*pointer) || *pointer == '_')) ? 1 : -1;
        state = ((*pointer == ':')) ? 2 : state;

        switch (state)
        {
        // Identifier doesn't exist
        case -1:
            terminated = true;
            pointer++;
            break;
        // Simulating Self Loop over State 1 for Reading any number of Characters until Space is encountered
        case 1:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 2:
            // Updating the Tokens Vector with new Token !
            tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}

void keywordDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    while (!terminated)
    {
        // If Space or Special Character is Encountered at State 1 Transition to State 2 else Stay on the same State
        // Note : handle cases of special characters appearing instead of Space !
        state = (isLetter(*pointer)) ? 1 : -1;
        state = ((*pointer == ' ' || isSpecialCharacter(*pointer))) ? 2 : state;

        switch (state)
        {
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 2:
            // Add Logic for Detecting Keywords !
            // Currently Handling All Tokens Except for 'else if'
            if (token_.lexeme == "function")
            {
                token_.tokenType = TokenType::Function;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "if")
            {
                token_.tokenType = TokenType::If;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "int")
            {
                token_.tokenType = TokenType::Int;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "else")
            {
                token_.tokenType = TokenType::Else;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "do")
            {
                token_.tokenType = TokenType::Do;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "until")
            {
                token_.tokenType = TokenType::Until;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "then")
            {
                token_.tokenType = TokenType::Then;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "read")
            {
                token_.tokenType = TokenType::Read;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "display")
            {
                token_.tokenType = TokenType::Display;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "displayline")
            {
                token_.tokenType = TokenType::DisplayLine;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "return")
            {
                token_.tokenType = TokenType::Return;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            }
            terminated = true;
            pointer++;
            break;
        }
    }
}

void specialCharacterDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    state = (isSpecialCharacter(*pointer)) ? 1 : -1;
    token_.lexeme += *pointer;
    while (!terminated)
    {
        switch (state)
        {
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            if(token_.lexeme == ","){
                token_.tokenType = TokenType::Comma;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            } else if(token_.lexeme == ":"){
                token_.tokenType = TokenType::Collon;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            } else if(token_.lexeme == ";"){
                token_.tokenType = TokenType::SemiCollan;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            } else if(token_.lexeme == "$"){
                token_.tokenType = TokenType::Dollar;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            } else if(token_.lexeme == "("){
                token_.tokenType = TokenType::OpenParenthesis;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            } else if(token_.lexeme == ")"){
                token_.tokenType = TokenType::CloseParenthesis;
                token_.lexeme = "null";
                // Updating the Tokens Vector with new Token !
                tokens.push_back(token_);
            } 
            terminated = true;
            pointer++;
            break;
        }
    }
}

void arithematicOperatorDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (isArithematicOperator(*pointer)) ? 1 : -1;
    token_.lexeme += *pointer;
    pointer++;

    while (!terminated)
    {
        switch (state)
        {
        case -1:
            terminated = true;
            // pointer++;
            break;
        case 1:
            if (token_.lexeme == "+" && *pointer == ' ') 
            {
                token_.tokenType = TokenType::Plus;
                token_.lexeme = "null";
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "-" &&  *pointer == ' ')
            {
                token_.tokenType = TokenType::Minus;
                token_.lexeme = "null";
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "*")
            {
                token_.tokenType = TokenType::Multiply;
                token_.lexeme = "null";
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "/")
            {
                token_.tokenType = TokenType::Divide;
                token_.lexeme = "null";
                tokens.push_back(token_);
            }
            else if (token_.lexeme == "%")
            {
                token_.tokenType = TokenType::Modulus;
                token_.lexeme = "null";
                tokens.push_back(token_);
            }
            terminated = true;
            break;
        }
    }
}


void variableDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (*pointer == '$') ? 1 : -1;
    pointer = (state == 1) ? (pointer+1) : pointer;
    // token_.lexeme += *pointer;
    // pointer++;
    while (!terminated)
    {
        state = ((*pointer == ' ' || isSpecialCharacter(*pointer)) && (state == 1)) ? 2 : state;
        switch (state)
        {
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 2:
            token_.tokenType = TokenType::Variable;
            terminated = true;
            tokens.push_back(token_);
            break;
        }
    }
}




void relationalOperatorDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    token_.tokenType = TokenType::RelationalOperator;
    state = (*pointer == '-') ? 1 : -1;
    while (!terminated)
    {
        // If Space is Encountered at State 1 Transition to State 2 else Stay on the same State
        state = ((*pointer == ' ') && state == 1) ? 2 : state;

        switch (state)
        {
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 2:
            // Updating the Tokens Vector with new Token !
            tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}


void commentDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (*pointer == '#') ? 1 : -1;
    pointer++;
    // state = (*pointer == '~') ? 2 : -1;
    // pointer++;

    while (!terminated)
    {
        state = (*pointer == '~' && state == 2) ? 3 : state;
        state = (*pointer == '#' && state == 3) ? 4 : state;

        switch (state)
        {
        case -1:
            terminated = true;
            break;
        case 1:
            state = (*pointer == '~') ? 2 : -1;
            pointer++;
            break;
        case 2:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 3:
            pointer++;
            break;
        case 4:
            pointer++;
            terminated = true;
            token_.tokenType = TokenType::Comment;
            tokens.push_back(token_);
            break;
        }
    }
}

void stringDFA(vector<char>::iterator &pointer)
{
   // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (*pointer == 39) ? 1 : -1;
    pointer++;
    // state = (*pointer == '~') ? 2 : -1;
    // pointer++;

    while (!terminated)
    {
        state = (*pointer == 39 && state == 1) ? 2 : state;
        // state = (*pointer == '#' && state == 3) ? 4 : state;

        switch (state)
        {
        case -1:
            terminated = true;
            break;
        case 1:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 2:
            pointer++;
            terminated = true;
            token_.tokenType = TokenType::Comment;
            tokens.push_back(token_);
            break;
        }
    }
}


void assignmentOperator(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    state = (*pointer == '=') ? 1 : -1;
    while (!terminated)
    {
        switch (state)
        {
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            token_.lexeme = "null";
            token_.tokenType = TokenType::AssignmentOperator;
            tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}

void startingBlockDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    state = (*pointer == '{') ? 1 : -1;
    while (!terminated)
    {
        switch (state)
        {
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            token_.lexeme = "null";
            token_.tokenType = TokenType::BlockStart;
            tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}

void numberDFA(vector<char>::iterator &pointer){
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (isNumber(*pointer)) ? 1 : -1;

    while(!terminated){
        state = (*pointer == ';' || *pointer == ')') ? 2 : state;
        switch(state){
            case -1:
                terminated = true;
                pointer++;
                break;
            case 1:
                token_.lexeme += *pointer;
                pointer++;
                break;
            case 2:
                token_.tokenType = TokenType::Number;
                if(token_.lexeme != "" && token_.lexeme != " ") tokens.push_back(token_);
                pointer++;
                terminated = true;
                break;
        }
    }
}


// void identifierDFA(vector<char>::iterator &pointer)
// {
//     // Set Up DFA Simulation
//     int state = 0;
//     bool terminated = false;
//     token token_;
//     token_.tokenType = TokenType::Identifier;
//     // If Reads Letter or UnderScore at State 0 transition to State 1
//     // Else Transition to State -1 Which is a Discarded State
//     while (!terminated)
//     {
//         // If Space is Encountered at State 1 Transition to State 2 else Stay on the same State
//         // Note : handle cases of special characters appearing instead of Space !
//         state = ((isLetter(*pointer) || *pointer == '_')) ? 1 : -1;
//         state = ((*pointer == ':')) ? 2 : state;

//         switch (state)
//         {
//         // Identifier doesn't exist
//         case -1:
//             terminated = true;
//             pointer++;
//             break;
//         // Simulating Self Loop over State 1 for Reading any number of Characters until Space is encountered
//         case 1:
//             token_.lexeme += *pointer;
//             pointer++;
//             break;
//         case 2:
//             // Updating the Tokens Vector with new Token !
//             tokens.push_back(token_);
//             terminated = true;
//             pointer++;
//             break;
//         }
//     }
// }



int main(int argc,char *argv[]){

    vector<char> stream = {'p','2','0',';','l','i','n','e','=','1','0',';','c',' ','d',39,';'};
    vector<char>::iterator it = stream.begin();
    while(it!=stream.end()){
        // keywordDFA(it);
    //    identifierDFA(it);
    //    specialCharacterDFA(it);
    //    arithematicOperatorDFA(it);
    //    relationalOperatorDFA(it);
        //   variableDFA(it);
        // commentDFA(it);
        // stringDFA(it);
        // assignmentOperator(it);
        // startingBlockDFA(it);
        numberDFA(it);
    }
    // Different Approach Loop

    // int counter = 0;
    // while(counter<=6){
    //     vector<char>::iterator it = stream.begin();
    //     while(it!=stream.end()){
    //         switch(counter){
    //             case 0:
    //                 keywordDFA(it);
    //                 break;
    //             case 1:
    //                 identifierDFA(it);
    //                 break;
    //             case 2:
    //                 specialCharacterDFA(it);
    //                 break;
    //             case 3:
    //                 relationalOperatorDFA(it);
    //                 break;
    //             case 4:
    //                 arithematicOperatorDFA(it);
    //                 break;
    //             case 5:
    //                 variableDFA(it);
    //                 break;
    //             case 6:
    //                 commentDFA(it);
    //                 break;
    //         }
    //     }
    //     counter++;
    // }

    
    for(auto x:tokens){
        x.Print();
    }

    return 0;
}