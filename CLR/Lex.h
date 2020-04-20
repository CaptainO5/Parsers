#include "CLR.h"

class Lexer{
    char las;
    string ip;
    public:
        int i;
        int line;
        Lexer();
        char scan();
        void readch();
};