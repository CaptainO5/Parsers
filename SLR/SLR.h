#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ctype.h>
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

uos FIRST(string S, Grammar& G);
uos FOLLOW(char N, Grammar& G, char N0=' ');

unordered_set<string> closure(unordered_set<string> I, Grammar& G);
unordered_set<string> GOTO(unordered_set<string> I, char X, Grammar& G);
int inIt(vector<unordered_set<string>> Sets, unordered_set<string> J);
vector<unordered_set<string>> items(Grammar& G);