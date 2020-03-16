#include "ll1Table.h"
#include "ParseTree.h"
#include "lexer.h"
#include <stack>

class Parser{
    private:
        char ip;
        stack<char> S;
        Table t;
        Lexer l;
    public:
        Parser();
        Parser(Table);
        Tree parse();
};