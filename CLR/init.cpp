#include "SLR.h"

Grammar::Grammar(){
    this -> S = 'S';
    this -> P.insert({{'S',"CC"}, {'C', "cC"}, {'C', "d"}});
    this -> N.insert({{'S', 0}, {'C', 1}});
    this -> T.insert({{'c', 0}, {'d', 1}, {'$', 2}});
}

Grammar::Grammar(string file){
    // TODO: load grammar from a file
}