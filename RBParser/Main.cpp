#include "parser.h"

int main(){
    Lexer l;
    Parser p(l);
    p.parse();
    cin.get();
}