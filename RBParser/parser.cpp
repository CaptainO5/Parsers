#include "parser.h"

void Parser::print(){
    for (int i = 0; op[i].tag != '$' ; i++)
        cout << op[i].lexeme << " ";
    cout << '\n';
}

void Parser::tokenize(Lexer l){
    int i = 0;
    do {
        init[i++] = l.scan();
    } while(init[i - 1].tag && i < 114);
    init[i] = Token('$');
}

bool Parser::match(string c){
    if (look.lexeme != c){// cout << look.lexeme << c;
        return false;}
    look = init[++i_cur];
    return true;
}

Parser::Parser(Lexer l) {
    tokenize(l);
    i_cur = o_cur = 0;
    look = init[i_cur];
}

int Parser::parse(){
    if (S()){
        op[o_cur] = Token('$');
        print();
        return 0;
    }
    cout << "\nError occured { Can't parse from \'"<< init[i_cur].lexeme << "\' }\n";
    print();
    return 1;
}

bool Parser::S(){
    int i_sv, o_sv;
    if (look.tag == ID || look.tag == NUM){
        i_sv = i_cur;
        o_sv = o_cur;
        if (F() && R()) return true;
        else {
            i_cur = i_sv;
            look = init[i_cur];
            o_cur = o_sv;
            if (! match(look.lexeme))   ;//cout << "\nError Encountered while parsing 1\n";
            else {
                op[o_cur++] = init[i_cur - 1];
                if (look.lexeme == "+" || look.lexeme == "-") {
                    if(! match("+") && ! match("-"))   ; //cout << "\nError Encountered while parsing 2\n";
                    else {
                        op[o_cur++] = init[i_cur - 1];
                        return S();
                    }   
                } else return true;
            }
        }
    }
    else if (look.lexeme == "("){
        i_sv = i_cur;
        o_sv = o_cur;
        if (F() && R()) return true;
        else {
            i_cur = i_sv;
            look = init[i_cur];
            o_cur = o_sv;
            if (! match("("))   ;// cout << "\nError Encountered while parsing 3\n";
            else {
                i_sv = i_cur;
                o_sv = o_cur;
                    if (T() && match(")") && R()) // cout << "\nError Encountered while parsing 6\n";
                        return true;
                    else{
                        i_cur = i_sv;
                        look = init[i_cur];
                        o_cur = o_sv;
                        S();
                        if (! match(")"))  ;// cout << "\nError Encountered while parsing 4\n";
                        return M();
                    }
            }
        }
    }
    return false;
}

bool Parser::F() {
    if (look.lexeme == "("){
        match("(");
        op[o_cur++] = init[i_cur - 1];
        if(look.tag == NUM || look.tag == ID){
            match(look.lexeme);
            op[o_cur++] = init[i_cur - 1];
        } else return false;
        if (match("+") || match("-")){
            op[o_cur++] = init[i_cur - 1];
        } else return false;
        S();
        if(match(")")){
            op[o_cur++] = init[i_cur - 1];
            return true;
        } else {cout << "Error: Missing closing brace.."; return false;}
    }
    else if(look.tag == NUM || look.tag == ID){
        match(look.lexeme);
        op[o_cur++] = init[i_cur - 1];
        return true;
    } else return false;
}

bool Parser::R() {
    int i_sv, o_sv;
    if (match("*") || match("/")){
        i_sv = i_cur;
        o_sv = o_cur;
        op[o_cur++] = init[i_cur - 1];
        if(F()) return true;
        else{
            i_cur = i_sv;
            look = init[i_cur];
            o_cur = o_sv;
            return S();
        }
    } else return false;
}

bool Parser::M() {
    if(look.lexeme == "+" || look.lexeme == "-"){
        if (match("+") || match("-")){
            op[o_cur++] = init[i_cur - 1];
            return S();
        }
        return false;
    }
    //if(look.tag != '$') return false;
    return true;
}

bool Parser::T(){
    if (look.tag == '('){
        if (! match("(")) ;//cout << "\nError Encountered while parsing 5\n";
        else T();
        return match(")");
    }
    if (look.tag == NUM || look.tag == ID){
        if(! F()) return false;
        R();
        return true;
    }
    return false;
}