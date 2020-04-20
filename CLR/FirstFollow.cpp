#include "SLR.h"

uos FIRST(string S, Grammar& G){
    int i = 0, len = S.length();
    bool cap = true, hasE = true;
    uos fs;
    while (i < len && cap && hasE) {
        cap = isupper(S[i]);
        if (cap){
            uos f;

            pair<umit, umit> iter = G.P.equal_range(S[i]);
            umit it1 = iter.first;

            while (it1 != iter.second){
                uos f2 = FIRST(it1 -> second, G);
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

uos FOLLOW(char N, Grammar& G, char N0){
    uos fs;

    if (N == G.S)
        fs.insert('$');
    umit it = G.P.begin();

    while (it != G.P.end()){
        string s = it -> second;
        int pos = s.find(N), len = s.length();
        while(pos != string::npos){
            bool hasE = false;
            if (pos + 1 != len) {
                uos f = FIRST(s.substr(pos + 1), G);
                hasE = f.erase('e');
                fs.insert(f.begin(), f.end());
            }
            if ((hasE || pos + 1 == len) && it -> first != N && it -> first != N0) {
                uos f = FOLLOW(it -> first, G, N);
                fs.insert(f.begin(), f.end());
            }
            s = s.substr(pos + 1);
            pos = s.find(N);
        }
        it++;
    }  
    return fs;
}