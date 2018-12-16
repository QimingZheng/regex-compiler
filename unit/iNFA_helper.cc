#include "matcher.h"

int main(){
    ofstream out;
    out.open("glushkov.nfa");
    out<<"# NFA\n";
    char regex[] = "(asd|fns*daj)*|fsj(dav)*f(fs|da)";
    int length = strlen(regex);
    AST ast(regex, length);
    GlushKov_NFA NFA(&ast);
    out<<to_string(NFA.state.size())<<endl;
    for(int i=0;i<NFA.state.size();i++){
        if(NFA.state[i]->is_final) out<<NFA.state[i]->state_id<<" : accepting 1\n";
        for(int j=0;j<NFA.state[i]->out_state.size();j++)
        out<<NFA.state[i]->state_id<<" -> "<<NFA.state[i]->out_state[j]->state_id<<" : "<<NFA.state[i]->out_state[j]->identifier<<endl;
    }
    return 0;
}
