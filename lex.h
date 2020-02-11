#include <iostream>
using namespace std;

const int NUM = 256, ID = 257;

class Token{
    public:
        int tag;
        string lexeme;
        Token();
        Token(int tag);
        Token(int, string);
};

class Lexer{
    char las;
    string ip;
    public:
        int i;
        int line;
        Lexer();
        Token scan();
        void readch();
        bool match(char);
};