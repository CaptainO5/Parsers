#include "ll1Table.h"

Table::Table() {
    this -> start = 'E';
    this -> G.insert({{'E', "TR"}, {'R', "+TR"}, {'R', "-TR"}, {'R', "e"}, {'T', "FU"}, 
                        {'U', "*F"}, {'U', "/F"}, {'U', "e"}, {'F', "V^F"}, {'F', "V"}, {'V', "(E)"}, {'V', "i"}});
    this -> N.insert({{'E', 0}, {'T', 1}, {'R', 2}, {'U', 3}, {'F', 4}, {'V', 5}});
    this -> T.insert({{'+', 0}, {'(', 1}, {')', 2}, {'*', 3}, {'/', 4}, {'-', 5}, {'$', 6}, {'i', 7}});

    for (auto& x: this -> G){
        cout << x.first << " -> " << x.second << endl;
    }

    uos f = follow('R');
    for (const char& i : f){
        cout << i <<" ";
    }

    fillT();
}

uos Table::first(string S){
    int i = 0, len = S.length();
    bool cap = true, hasE = true;
    uos fs;
    while (i < len && cap && hasE) {
        cap = isupper(S[i]);
        if (cap){
            uos f;

            pair<umit, umit> iter = (this -> G).equal_range(S[i]);
            umit it1 = iter.first;

            while (it1 != iter.second){
                uos f2 = first(it1 -> second);
                f.insert(f2.begin(), f2.end());
                it1++;
            }
            hasE = f.erase('e');
            fs.insert(f.begin(), f.end());
        } else{
            fs.insert(S[i]);
            hasE = false;
        }
        i++;
    }

    if (i == len && hasE){
        fs.insert('e');
    }
    return fs;
}

uos Table::follow(char N){
    uos fs;

    if (N == this -> start)
        fs.insert('$');
    umit it = (this -> G).begin();

    while (it != (this -> G).end()){
        string s = it -> second;
        int pos = s.find(N), len = s.length();
        while(pos != string::npos){
            bool hasE = false;
            if (pos + 1 != len) {
                uos f = first(s.substr(pos + 1));
                hasE = f.erase('e');
                fs.insert(f.begin(), f.end());
            }
            if ((hasE || pos + 1 == len) && it -> first != N) {
                uos f = follow(it -> first);
                fs.insert(f.begin(), f.end());
            }
            s = s.substr(pos + 1);
            pos = s.find(N);
        }
        it++;
    }  
    return fs;
}

void Table::fillT(){
    
}

int main(){
    Table t;
}