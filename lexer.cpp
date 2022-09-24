#include "lexer.h"
using namespace std;
// for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE"};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
// Changed Ordering of the Print Method -> (token,lexeme)
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << tokenType << " , "
         << lexeme << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}
bool lexer::isLetter(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? true : false;
}
bool lexer::isSpecialCharacter(char ch)
{
    return (ch == ':' || ch == ';' || ch == ',' || ch == '$' || ch == '(' || ch == ')') ? true : false;
}
bool lexer::isArithematicOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') ? true : false;
}
bool lexer::isNumber(char ch){
    return (ch>='0' && ch<='9') ? true : false;
}

bool lexer::isKeyword(string str){
    return (str == "function" || str == "if" || str == "else" || str == "int" || str == "then" || str == "do" 
    || str == "while" || str == "display" || str == "displayline" || str == "read" || str == "return") ? true : false;
}

bool lexer::isRelationalOperator(string str){
    return (str == "-lt" || str == "-gt" || str == "-eq" || str == "-le" || str == "-ge") ? true : false; 
}

// Done
void lexer::identifierDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    token_.tokenType = TokenType::Identifier;
   
    while (!terminated)
    {
        state = ((isLetter(*pointer) || *pointer == '_')) ? 1 : -1;
        state = ((*pointer == ':')) ? 2 : state;

        switch (state)
        {
        // Identifier doesn't exist
        case -1:
            terminated = true;
            pointer++;
            break;
        case 1:
            token_.lexeme += *pointer;
            pointer++;
            break;
        case 2:
            if(!isKeyword(token_.lexeme)) tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}

// Done
void lexer::keywordDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
   
    while (!terminated)
    {
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

// Done
void lexer::relationalOperatorDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    token_.tokenType = TokenType::RelationalOperator;
    state = (*pointer == '-') ? 1 : -1;
    while (!terminated)
    {
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
            if(isRelationalOperator(token_.lexeme)) tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}

// Done
void lexer::specialCharacterDFA(vector<char>::iterator &pointer)
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

// Done
void lexer::arithematicOperatorDFA(vector<char>::iterator &pointer)
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

// Done
void lexer::variableDFA(vector<char>::iterator &pointer)
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
        state = ((*pointer == ' ' || isSpecialCharacter(*pointer) || isArithematicOperator(*pointer)) && (state == 1)) ? 2 : state;
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

// Done
void lexer::commentDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (*pointer == '#') ? 1 : -1;
    pointer++;

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


void lexer::stringDFASingleQuote(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (*pointer == 39 && (*(pointer-1) == ' ' || *(pointer-1) == ':')) ? 1 : -1;
    pointer++;

    while (!terminated)
    {
        state = (*pointer == 39 && state == 1) ? 2 : state;

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

void lexer::stringDFADoubleQuote(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (*pointer == 34) ? 1 : -1;
    pointer++;


    while (!terminated)
    {
        state = (*pointer == 34 && state == 1) ? 2 : state;

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


void lexer::assignmentOperator(vector<char>::iterator &pointer)
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

void lexer::startingBlockDFA(vector<char>::iterator &pointer)
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

void lexer::closingBlockDFA(vector<char>::iterator &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    state = (*pointer == '}') ? 1 : -1;
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
            token_.tokenType = TokenType::BlockEnd;
            tokens.push_back(token_);
            terminated = true;
            pointer++;
            break;
        }
    }
}



void lexer::numberDFA(vector<char>::iterator &pointer){
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;

    state = (isNumber(*pointer)) ? 1 : -1;

    while(!terminated){
        state = (*pointer == ';' || *pointer == ')' || *pointer == ' ') ? 2 : state;
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

void lexer::Tokenize() // function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
    // your implementation goes here
    int counter = 0;
    while(counter<=11){
    while(it != stream.end()){
        switch(counter){
            case 0:
                keywordDFA(it);
                break;
            case 1:
                variableDFA(it);
                break;
            case 2:
                identifierDFA(it);
                break;
            case 3:
                relationalOperatorDFA(it);
                break;
            case 4:
                specialCharacterDFA(it);
                break;
            case 5:
                arithematicOperatorDFA(it);
                break;
            case 6:
                commentDFA(it);
                break;
            case 7:
                stringDFASingleQuote(it);
                break;
            case 8:
                stringDFADoubleQuote(it);
                break;
            case 9:
                startingBlockDFA(it);
                break;
            case 10:
                closingBlockDFA(it);
                break;
            case 11:
                numberDFA(it);
                break;
        }
    }
    counter++;
    it = stream.begin();
    }
    // push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    // constructors: takes file name as an argument and store all
    // the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) // if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { // store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' '); // dummy spaces appended at the end
        stream.push_back(' ');
        // Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        // assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    // helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    // this function will return single (token,lexeme) pair on each call
    // this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                             // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}