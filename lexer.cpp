#include "lex.h"
#include <ctype.h>

Token::Token(int tag){
    this -> tag = tag;
}

Token::Token(int tag, string l){
    this -> tag = tag;
    lexeme = l;
}

Token::Token(){
    tag = 0;
}

Lexer::Lexer(){
    las =' ';
    line = 1;
    getline(cin, ip);
    i = 0;
}

void Lexer::readch(){
    las = ip[i++];
}

Token Lexer::scan(){
    // Skip white spaces
    for (;;readch()) {
        if (las == ' ' || las == '\t') continue; 
        else if(las == '\n') line++;
        else break;   
    }

    switch(las) {
        case '+':
            readch(); return Token(int('+'), "+");
        case '-':
            readch(); return Token(int('-'), "-");
        case '*':
            readch(); return Token(int('*'), "*");
        case '/':
            readch(); return Token(int('/'), "/");
        case '(':
            readch(); return Token(int('('), "(");
        case ')':
            readch(); return Token(int(')'), ")");
    }
    string l = "";
    if (isdigit(las)){
        do{
            l += las;
            readch();
        } while(isdigit(las));
        return Token(NUM, l);
    }

    if(isalpha(las)){
        do{
            l += las;
            readch();
        } while(isalnum(las));
        return Token(ID, l);
    }

    return Token(0);
}

// int main(){
//     Lexer l;
//     Token r;
//     do {
//         r = l.scan();
//         cout << r.tag << '\t' << r.lexeme << '\n';
//     } while(r.tag);
// }