#include "Parser.h"

Parser::Parser(){
    S.push(0);
}

void Parser::parse(string Action[][10], int Goto[][10], Grammar& G){
    cout << "Enter a string to Parse: ";
    Lexer l;
    char ip = l.scan();
    while (true) {
        string a = Action[S.top()][G.T.find(ip) -> second];
        if (a[0] == 's'){
            S.push(a[1] - '0');
            ip = l.scan();
        } else if (a[0] == 'r'){
            for (int i = 0; i < a.size()-6; i++)
                S.pop();
            int j = Goto[S.top()][G.N.find(a[1]) -> second];
            S.push(j);
        } else if (a[0] == 'a'){
            cout << "\nString is accepted\n";
            return;
        } else {
            cout << "\nCannot accept\n";
            return;
        }
        stack<int> temp = S;
        while(temp.size() != 0){
            cout << temp.top() << "  ";
            temp.pop();
        } 
        cout << endl;
    }
}