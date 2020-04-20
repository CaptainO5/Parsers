#include "SLR.h"

Grammar::Grammar(){
    this -> S = 'S';
    this -> P.insert({{'S', "L=R"}, {'S', "R"}, {'L', "*R"}, {'L', "i"}, {'R', "L"}});
    this -> N.insert({{'S', 0}, {'R', 1}, {'L', 2}});
    this -> T.insert({{'=', 0}, {'*', 1}, {'i', 2}});
}

Grammar::Grammar(string file){
    // TODO: load grammar from a file
}