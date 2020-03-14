#include "ll1Table.h"

Grammar::Grammar(){
    // For future abstraction
}

Table::Table() {
    this -> start = 'E';
    this -> G.insert({{'E', "TR"}, {'R', "+TR"}, {'R', "-TR"}, {'R', "e"}, {'T', "FU"}, 
                        {'U', "*F"}, {'U', "/F"}, {'U', "e"}, {'F', "VM"}, {'M', "^VM"},
                        {'M', "e"}, {'V', "(E)"}, {'V', "i"}});
    this -> N.insert({{'E', 0}, {'T', 1}, {'R', 2}, {'U', 3}, {'F', 4}, {'V', 5}, {'M', 6}});
    this -> T.insert({{'+', 0}, {'(', 1}, {')', 2}, {'*', 3}, {'/', 4}, {'-', 5}, {'$', 6}, {'i', 7}, {'^', 8}});

    for (int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            this -> table[i][j] = this -> G.end();
        }
    }

    fillT();

    // Print Productions
    // for (auto& x: this -> G){
    //     cout << x.first << " -> " << x.second << endl;
    // }

    // Print first and follow sets
    // cout << "FOLLOW\n";
    // for (auto i : N){
    //     uos f = follow(i.first);
    //     cout << i.first << ": ";
    //     for (const char& j : f){
    //         cout << j <<" ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\nFIRST\n";
    // for (auto i : N){
    //     string s = "";
    //     s += i.first;
    //     uos f = first(s);
    //     cout << i.first << ": ";
    //     for (const char& j : f){
    //         cout << j <<" ";
    //     }
    //     cout << "\n";
    // }
    
    // Print LL(1) parsing table entries
    //printT();
}

Table::Table(Grammar G) {
    this -> G = G.P;
    this -> N = G.N;
    this -> T = G.T;
    this -> start = G.S;

    for (int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            this -> table[i][j] = this -> G.end();
        }
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
    for (umit it = this -> G.begin(); it != this -> G.end(); it++) {
        int n = this -> N.find(it -> first) -> second;
        int t = 0;
        uos f = first(it -> second);
           //cout <<"\n"<< it -> first <<" -> "<< it -> second << "\n\t";
        bool hasE = f.erase('e');
        for (char i : f) {
            t = this -> T.find(i) -> second;
               //cout << i << "\t" << n << "," << t << "\n\t";
            table[n][t] = it;
        }
        if (hasE) {
            uos f1 = follow(it -> first);
               //cout << "\nfollow  " << it -> first << "\n\t";
            for (char i : f1){
                t = this -> T.find(i) -> second;
                   //cout << i << "\t" << n << "," << t << "\n\t";
                table[n][t] = it;
            }
        }
    }
}

void Table::printT(){
    for(int i = 0; i < 7; i++){
        for (int j = 0; j < 9; j++){
            umit e = this -> table[i][j];
            if(e != this->G.end())
                cout << e -> first << " -> " << e -> second << "\t\t";
            else
                cout << "\t\t";
        }
        cout << endl;
    }
}