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

        void print();        
        void tokenize(Lexer);
        bool match(string c);

    public: 
        Parser(Lexer);

        int parse();
};