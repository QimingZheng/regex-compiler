#include "parser.cc"

class GlushKov_NFA{
public:
    GlushKov_NFA(AST *ast){ this.ast = ast;}
    AST *ast;
    vector<int> state;
};