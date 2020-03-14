#include "ll1Table.h"
#include "ParseTree.h"
#include <stack>

class Parser{
    private:
        string input;
        stack<char> S;
        Table t;
    public:
        Parser();
        Parser(Table);
        Tree parse();
};