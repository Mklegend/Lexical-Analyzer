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
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
         << reserved[(int)tokenType] << "}\n";
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
bool lexer::isSpecialCharacter(char)
{
    return (ch == ':' || ch == ';' || ch == ',' || ch == '$' || ch == '(' || ch == ')') ? true : false;
}
void lexer::identifierDFA(int &pointer)
{
    // Set Up DFA Simulation
    int state = 0;
    bool terminated = false;
    token token_;
    token_.tokenType = TokenType::Identifier;
    while (!terminated)
    {
        // If Reads Letter or UnderScore at State 0 transition to State 1
        // Else Transition to State -1 Which is a Discarded State
        state = ((isLetter(stream[pointer]) || stream[pointer] == '_') && state == 0) ? 1 : -1;

        // If Space is Encountered at State 1 Transition to State 2 else Stay on the same State
        // Note : handle cases of special characters appearing instead of Space !
        state = ((stream[pointer] == ' ' || isSpecialCharacter(stream[pointer])) && state == 1) ? 2 : state;

        switch (state)
        {
        // Identifier doesn't exist
        case -1:
            terminated = true;
            break;
        // Simulating Self Loop over State 1 for Reading any number of Characters until Space is encountered
        case 1:
            token_.lexeme += stream[pointer];
            pointer = pointer + 1;
        case 2:
            // Updating the Token Vector with new Token !
            tokens.push_back(token_);
            terminated = true;
            break;
        }
    }
}
void lexer::Tokenize() // function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
    // your implementation goes here

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