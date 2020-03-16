#include "ll1parser.h"

Parser::Parser(){
    S.push('$');
    S.push(t.start);
    cout << "Enter a string to Parse: ";
    ip = l.scan();
}

Parser::Parser(Table t){
    this -> t = t;
    Parser();
}

Tree::Tree(){}

Tree Parser::parse(){
    Tree pt;
    while (ip != EOF) {
        while (ip != S.top()) {
            unordered_map<char, int>::iterator n_it = t.N.find(S.top());
            unordered_map<char, int>::iterator t_it = t.T.find(ip);
            if (n_it == t.N.end() || t_it == t.T.end()){
                cout << "\nError Parsing.. inut token: " << ip << ", top of stack: " << S.top() << "\n";
                return pt;
            }
            umit p = t.table[n_it -> second][t_it -> second];
            if (p == t.G.end()){
                cout << "\nError Parsing.. inut token: " << ip << "\n";
                return pt;
            }
            cout << "<" << S.top() << ", " << ip << "> " <<"\n";
            cout << p -> first << " -> " << p -> second << "\n";
            string r = p -> second;
            S.pop();
            for (int j = r.length() - 1; j >= 0; j--){
                if (r[j] != 'e')
                    S.push(r[j]);
            }
            stack<char> temp = S;
            while(!temp.empty()){
                cout << temp.top() << " ";
                temp.pop();
            }
            cout << "\n\n";
        }
        cout << "<" << S.top() << ", " << ip << ">";
        S.pop();
        cout << "\tpopped\n\n";
        ip = l.scan();
    }
}

int main(){
    Parser p;
    p.parse();
}