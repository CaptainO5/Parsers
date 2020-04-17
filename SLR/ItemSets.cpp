#include "G.h"
#include <ctype.h>
#include <vector>

unordered_set<string> closure(unordered_set<string> I, Grammar G){
    unordered_set<string> J = I;
    bool isAdded[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while(true){
        unordered_set<string> temp = J;
        for (string i: J){
            int pos = i.find('.', 2);

            if (pos == string::npos)
                throw "Invalid item";
            
            if (isupper(i[pos+1])){
                if(G.N.find(i[pos+1]) == G.N.end())
                    throw "Invalid item";
                
                int NT = G.N.find(i[pos+1]) -> second;
                if(!isAdded[NT]){
                    pair<umit, umit> it = G.P.equal_range(i[pos+1]);
                    for (umit it1 = it.first; it1 != it.second; it1++){
                        string item = " ." + it1 -> second;
                        item.insert(item.begin(), it1 -> first);
                        temp.insert(item);
                    }
                }
                isAdded[NT] = true;
            }
        }
        int prev = J.size();
        J.insert(temp.begin(), temp.end());
        int after = J.size();
        if (prev == after)
            return J;
    }
}

unordered_set<string> GOTO(unordered_set<string> I, char X, Grammar G){
    unordered_set<string> temp;
    for (string i: I){
        int pos = 0;
        do {
            pos = i.find(X, 2+pos);
        } while (pos != i.npos && i[pos-1] !='.');
        if (pos!= string::npos && i[pos-1] == '.'){
            i.erase(pos-1, 1);
            i.insert(pos, ".");
            temp.insert(i);
        }
    }
    return closure(temp, G);
}

vector<unordered_set<string>> items(Grammar G){

}

int main(){
    Grammar G;
    unordered_set<string> I = {"S' .S"};
    try {
        I = closure(I, G);
        // for (string i: I){
        //         i.insert(2, "-> ");
        //         cout << i  << endl;
        //     }
        for (auto x: G.N){
            cout << x.first << endl;
            unordered_set<string> J = GOTO(I, x.first, G);
            for (string i: J){
                i.insert(2, "-> ");
                cout << i  << endl;
            }
            cout << endl;
        }
        for (auto x: G.T){
            cout << x.first << endl;
            unordered_set<string> J = GOTO(I, x.first, G);
            for (string i: J){
                i.insert(2, "-> ");
                cout << i  << endl;
            }
            cout << endl;
        }
    } catch (char const *m){
        cout << m;
    }
    return 0;
}