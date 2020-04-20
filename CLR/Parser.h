#include "Lex.h"
#include <stack>
class Parser{
    private:
        char ip;
        stack<int> S;
        Lexer l;
    public:
        Parser();
        void parse(string Action[][10], int Goto[][10], Grammar& G);
};