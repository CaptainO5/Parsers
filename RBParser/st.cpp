#include "st.h"

Node::Node(){
            this -> next = NULL;
}

Node::Node(Token t){
    this -> t = t;
    this -> next = NULL;
}

SymbolTable::SymbolTable(){
    for (int i = 0; i < this -> LIMIT; i ++){
        ST[i] = NULL;
    }
}

int SymbolTable::hashFunc(string id){
    int sum = 0;
    for (int i = 0; id[i] != '\0'; i++){
        sum += id[i];
    }
    return sum % LIMIT;
}

bool SymbolTable::insert(Token t){
    int h = hashFunc(t.lexeme);
    Node * n = new Node(t);
    if (! ST[h]) {
        ST[h] = n;
        return true;
    } else {
        Node * p = ST[h];
        for(; p -> next; p = p -> next);
        p -> next = n;
        return true;
    }
    return false;
}

Token SymbolTable::lookUp(string l){
    int h = hashFunc(l);
    if (ST[h] -> t.lexeme == l) {
        return ST[h] -> t;
    } else if(ST[h] -> next) {
        Node * p = ST[h] -> next;
        for(; p; p = p -> next){
            if (p -> t.lexeme == l)
                return p -> t;
        }
    }
    return Token(0);
}