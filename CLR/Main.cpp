#include "Parser.h"

int main(){
    Grammar G;
    vector<unordered_set<string>> Items = items(G);
    int icount = Items.size(), t = G.T.size(), n = G.N.size();
    string Action[icount][10];
    int Goto[icount][10];
    bool conflict = false;

    int id = 0;
    cout << "Item Sets:\n";
    for (auto I: Items){
        cout << "I" << id++ << endl;
        for (string i: I){
            i.insert(2, "-> ");
            i.insert(i.end()-2, ',');
            cout << i  << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < icount; i++)
        for (int j = 0; j < t; j++)
            Action[i][j] = "E";

    for (int i = 0; i < icount; i++)
        for (int j = 0; j < n; j++)
            Goto[i][j] = -1;

    for (int i = 0; i < icount; i++){
        for (string p: Items[i]){
            int pos = p.find('.');
            if (pos + 1 != p.size()-2){
                char a = p[pos+1];
                int j = inIt(Items, GOTO(Items[i], a, G));
                if (!isupper(a)){
                    string val = "s" + to_string(j);
                    if (Action[i][G.T.find(a)->second][0] != 'r') 
                        Action[i][G.T.find(a)->second] = val; 
                    else {
                        Action[i][G.T.find(a)->second] = "C";
                        conflict = true;
                    }
                } else {
                    Goto[i][G.N.find(a)->second] = j;
                }
            } else if (p[1] != '\''){
                char a = p[p.size() - 1];

                if (Action[i][G.T.find(a)->second] == "E") 
                    Action[i][G.T.find(a)->second] = "r" + p; 
                else {
                    Action[i][G.T.find(a)->second] = "C";
                    conflict = true;
                }
                
            } else{
                Action[i][G.T.find('$')->second] = "accept";
            }
        }
    }

    // Printing tables
    cout << "\nACTION\n\nI\t";
    for (int i = 0; i < G.T.size(); i++){
        cout << i << "\t";
    }    
    cout << endl;

    for (int i = 0; i < icount; i++){
        cout << i << '\t';
        for (int j = 0; j < t; j++){
            if (Action[i][j] != "E")
                cout << Action[i][j];
            cout << "\t";
        }
        cout << endl;
    }
    cout << "---\t";
    for (auto x: G.T){
        cout << x.second << ": " << x.first << "\t";
    }    
    cout << "---\n";

    cout << "\n\nGOTO\n\nI\t";
    for (int i = 0; i < G.N.size(); i++){
        cout << i << "\t";
    }    
    cout << endl;

    for (int i = 0; i < icount; i++){
        cout << i << '\t';
        for (int j = 0; j < n; j++){
            if (Goto[i][j] >= 0) 
                cout << Goto[i][j];
            cout << "\t";
        }
        cout << endl;
    }
    cout << "---\t";
    for (auto x: G.N){
        cout << x.second << ": " << x.first << "\t";
    }    
    cout << "---\n";

    if (conflict)
        cout << "\n*** THE GRAMMAR IS NOT CLR(1) ***\n\n";
    else{
        Parser p;
        p.parse(Action, Goto, G);
    }
    
    return 0;
}