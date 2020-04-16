#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef unordered_multimap<char, string>::iterator umit; 
typedef unordered_set<char> uos;

class Grammar{
    public:
        // Grammar
        unordered_multimap <char, string> P;
        char S;
        unordered_map<char, int> N;
        unordered_map<char, int> T;
        Grammar();
        Grammar(string file);
};