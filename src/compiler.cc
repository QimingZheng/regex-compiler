#include "compiler.h"

void GlushKov_NFA::label_ast_to_nfa(ast_node *_ast) {
    queue<ast_node *> Q;
    Q.push(_ast);
    int cnt = 0;
    while(!Q.empty()){
        ast_node *cur = Q.front();
        Q.pop();
        if(cur->node_type==1){
            cnt+=1;
            cur->ids=cnt;
            state_node *_state = new state_node(cnt, cur->identifier);
            state.push_back(_state);
        }
        else{
            for(int i=0;i<cur->child.size();i++)
                Q.push(cur->child[i]);
        }
    }
    return;
}

