#include "Lex.h"

Lexer::Lexer(){
    las =' ';
    line = 1;
    getline(cin, ip);
    ip += "$";
    i = 0;
}

void Lexer::readch(){
    this -> las = ip[this->i++];
}

char Lexer::scan(){
    // Skip white spaces
    while(true){
        readch();
        if (this->las == ' ' || this->las == '\t') continue; 
        else if(this->las == '\n') return '$';
        else break;   
    }
    return this -> las;
}