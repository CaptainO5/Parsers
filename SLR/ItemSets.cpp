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

int main(){
    Grammar G;
    unordered_set<string> I = {"S' .S"};
    I = closure(I, G);
    for (string i: I){
        cout << i << endl;
    }
}