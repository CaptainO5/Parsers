#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef unordered_multimap<char, string>::iterator umit; 
typedef unordered_set<char> uos;

class Table {
    private:
        uos first(string);
        uos follow(char);
        void fillT();
    public:
        // Grammar
        unordered_multimap <char, string> G;
        char start;
        unordered_map<char, int> N;
        unordered_map<char, int> T;

        // LL(1) parsing table
        umit table[20][20];

        void printT();
        Table();
};