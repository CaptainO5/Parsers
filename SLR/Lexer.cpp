#include "Lex.h"

Lexer::Lexer(){
    las =' ';
    line = 1;
}

void Lexer::readch(){
    cin.get(las);
}

char Lexer::scan(){
    // Skip white spaces
    for (;;readch()) {
        if (las == ' ' || las == '\t') continue; 
        else if(las == '\n') {line++; return '$';}
        else break;   
    }

    switch(las) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '^':
        case '$':
            char temp = las; readch(); return temp;
    }

    string l = "";
    if (isdigit(las)){
        do{
            l += las;
            readch();
        } while(isdigit(las));
        return 'i';
    }

    if(isalpha(las)){
        do{
            l += las;
            readch();
        } while(isalnum(las));
        return 'i';
    }

    return 0;
}