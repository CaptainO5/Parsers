#include "SLR.h"

class Lexer{
    private:
        char las;
        void readch();
    public:
        int line;
        Lexer();
        char scan();
};