#include "st.h"

class Parser{
    private:
        Token init[115];
        Token look;
        Token op[115];
        int i_cur, o_cur;

        bool S();
        bool F();
        bool R();
        bool M();

        void tokenize(Lexer l){
            int i = 0;
            do {
                init[i++] = l.scan();
            } while(init[i].tag && i < 114);
            init[i] = Token('$');
        }

        bool match(string c){
            if (look.lexeme != c)
                return false;
            look = init[++i_cur];
            return true;
        }

    public: 
        Parser(Lexer l) {
            tokenize(l);
            i_cur = o_cur = 0;
            look = init[i_cur];
        }

        int parse(){
            if (! S()){
                cout << "\nError occured\n";
            }
        }
};

bool Parser::S(){
    int i_sv, o_sv;
    if (look.tag == ID || look.tag == NUM){
        i_sv = i_cur;
        o_sv = o_cur;
        if (F() && R()) return true;
        else {
            i_cur = i_sv;
            o_cur = o_sv;
            if (! match(look.lexeme))   cout << "\nError Encountered while parsing\n";
            else {
                op[o_cur++] = init[i_cur - 1];
                if (look.lexeme == "+" || look.lexeme == "-") {
                    if(! match("+") && ! match("-"))   cout << "\nError Encountered while parsing\n";
                    else {
                        op[o_cur++] = init[i_cur - 1];
                        return S();
                    }   
                }
            }
        }
    }
    else if (look.lexeme == "("){
        i_sv = i_cur;
        o_sv = o_cur;
        if (F()) R();
        else {
            i_cur = i_sv;
            o_cur = o_sv;
            if (! match("("))   cout << "\nError Encountered while parsing\n";
            else {
                S();
                if (! match(")"))   cout << "\nError Encountered while parsing\n";
                else return M();
            }
        }

    }
    return true;
}

bool Parser::F() {

}