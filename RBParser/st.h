#include "lex.h"

class Node{
    public:
        Token t;
        Node* next;
        Node();
        Node(Token);
};

class SymbolTable{
    private:
        const static int LIMIT = 101;
        Node * ST[LIMIT];
        int hashFunc(string id);
    public:
        bool insert(Token);
        Token lookUp(string);
        SymbolTable();
};