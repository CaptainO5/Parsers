#include "Lex.h"
#include <stack>
class Parser{
    private:
        stack<int> S;
    public:
        Parser();
        void parse(string Action[][10], int Goto[][10], Grammar& G);
};