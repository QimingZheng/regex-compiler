#ifndef COMPILER_CC
#define COMPILER_CC
#include "compiler.h"

GlushKov_NFA::GlushKov_NFA(AST *ast){

    this->ast = ast;
    label_ast_to_nfa(this->ast->root);
    state_node *start = new state_node(0,-6);
    state.push_back(start);
    entrance = start;
    // calculate null-set
    if(V_set(this->ast->root)) {start->is_final = true;}

    //calculate prefix set and link start to prefix state
    vector<int> P = Prefix_set(this->ast->root);
    for(int i=0;i<P.size();i++)
    {
        for(int j=0;j<state.size();j++)
        {
            if(state[j]->state_id == P[i])
            {
                start->out_state.push_back(state[j]);
                state[j]->in_state.push_back(start);
                break;                
            }
        }
    }

    //calculate suffix set and mark suffix state's is_final flag
    vector<int> D = Suffix_set(this->ast->root);
    for(int i=0;i<D.size();i++)
    {
        for(int j=0;j<state.size();j++)
        {
            if(state[j]->state_id == D[i])
            {
                state[j]->is_final=true;
                break;
            }
        }
    }

    //calculate neighbor-edge set and link src state to dst state
    vector<edge_pair> F = Neighbor_set(this->ast->root);
    for(int i=0; i<F.size();i++)
    {
        for(int j=0;j<state.size();j++){
            if(state[j]->state_id!=F[i].src_ids) continue;
            for(int k=0;k<state.size();k++)
            {
                if(state[k]->state_id!=F[i].dst_ids) continue;
                state[j]->out_state.push_back(state[k]);
                state[k]->in_state.push_back(state[j]);
                break;
            }
            break;
        }
    }
}

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

bool GlushKov_NFA::V_set(ast_node *_ast){
    if (_ast->node_type==1){_ast->_V_set = false; return false;}
    else{
        if (_ast->op_type == -3){
            V_set(_ast->child[0]);
            _ast->_V_set = true;
            return _ast->_V_set;
        }
        if (_ast->op_type == -4){
            V_set(_ast->child[0]);
            V_set(_ast->child[1]);
            _ast->_V_set = (_ast->child[0]->_V_set || _ast->child[1]->_V_set);
            return _ast->_V_set;
        }
        if (_ast->op_type == -5){
            V_set(_ast->child[0]);
            V_set(_ast->child[1]);
            _ast->_V_set = (_ast->child[0]->_V_set && _ast->child[1]->_V_set);
            return _ast->_V_set;
        }
    }
}

vector<int> GlushKov_NFA::Prefix_set(ast_node *_ast){
    if (_ast->node_type==1){_ast->_Prefix_set.push_back(_ast->ids); return _ast->_Prefix_set;}
    else{
        if (_ast->op_type == -3){
            _ast->_Prefix_set = Prefix_set(_ast->child[0]);
            return _ast->_Prefix_set;
        }
        if (_ast->op_type == -4){
            Prefix_set(_ast->child[0]);
            Prefix_set(_ast->child[1]);
            _ast->_Prefix_set = vector_union(_ast->child[0]->_Prefix_set, _ast->child[1]->_Prefix_set);
            return _ast->_Prefix_set;
        }
        if (_ast->op_type == -5){
            Prefix_set(_ast->child[0]);
            Prefix_set(_ast->child[1]);
            if (_ast->child[0]->_V_set)
                _ast->_Prefix_set = vector_union(_ast->child[0]->_Prefix_set, _ast->child[1]->_Prefix_set);
            else
                _ast->_Prefix_set = _ast->child[0]->_Prefix_set;
            return _ast->_Prefix_set;
        }
    }
}

vector<int> GlushKov_NFA::Suffix_set(ast_node *_ast){
    if (_ast->node_type==1){_ast->_Suffix_set.push_back(_ast->ids); return _ast->_Suffix_set;}
    else{
        if (_ast->op_type == -3){
            _ast->_Suffix_set = Suffix_set(_ast->child[0]);
            return _ast->_Suffix_set;
        }
        if (_ast->op_type == -4){
            Suffix_set(_ast->child[0]);
            Suffix_set(_ast->child[1]);
            _ast->_Suffix_set = vector_union(_ast->child[0]->_Suffix_set, _ast->child[1]->_Suffix_set);
            return _ast->_Suffix_set;
        }
        if (_ast->op_type == -5){
            Suffix_set(_ast->child[0]);
            Suffix_set(_ast->child[1]);
            if (_ast->child[1]->_V_set)
                _ast->_Suffix_set = vector_union(_ast->child[1]->_Suffix_set, _ast->child[0]->_Suffix_set);
            else
                _ast->_Suffix_set = _ast->child[1]->_Suffix_set;
            return _ast->_Suffix_set;
        }
    }
}

vector<edge_pair> GlushKov_NFA::Neighbor_set(ast_node *_ast){
    if (_ast->node_type==1){_ast->_Neighbor_set.clear(); return _ast->_Neighbor_set;}
    else{
        if (_ast->op_type == -3){
            Neighbor_set(_ast->child[0]);
            vector<int> P = _ast->child[0]->_Prefix_set;
            vector<int> D = _ast->child[0]->_Suffix_set;
            vector<edge_pair> D_P;
            for(int i=0;i<D.size();i++)
            {
                for(int j=0;j<P.size();j++)
                {
                    D_P.push_back(edge_pair(D[i],P[j]));
                }
            }
            _ast->_Neighbor_set = vector_union(_ast->child[0]->_Neighbor_set, D_P);
            return _ast->_Neighbor_set;
        }
        if (_ast->op_type == -4){
            Neighbor_set(_ast->child[0]);
            Neighbor_set(_ast->child[1]);
            _ast->_Neighbor_set = vector_union(_ast->child[0]->_Neighbor_set, _ast->child[1]->_Neighbor_set);
            return _ast->_Neighbor_set;
        }
        if (_ast->op_type == -5){
            Neighbor_set(_ast->child[0]);
            Neighbor_set(_ast->child[1]);
            vector<int> D = _ast->child[0]->_Suffix_set;
            vector<int> P = _ast->child[1]->_Prefix_set;
            vector<edge_pair> D_P, tmp;
            for(int i=0;i<D.size();i++)
            {
                for(int j=0;j<P.size();j++)
                {
                    D_P.push_back(edge_pair(D[i],P[j]));
                }
            }
            tmp = vector_union(_ast->child[0]->_Neighbor_set, _ast->child[1]->_Neighbor_set);
            _ast->_Neighbor_set = vector_union(tmp, D_P);
            return _ast->_Neighbor_set;
        }
    }
}

template <typename T>
vector<T> vector_union(vector<T> &a, vector<T> &b){
    vector<T> re;
    re.clear();
    for(int i=0;i<a.size();i++)
    {
        bool added = false;
        for(int j=0;j<re.size();j++)
            if(a[i]==re[j]) {added = true; break;}
        if (!added) re.push_back(a[i]);
    }
    for(int i=0;i<b.size();i++)
    {
        bool added = false;
        for(int j=0;j<re.size();j++)
            if(b[i]==re[j]) {added = true; break;}
        if (!added) re.push_back(b[i]);
    }
    return re;
}


void GlushKov_NFA::traverse(){
    ofstream dot_graph;
    dot_graph.open("nfa_graph.dot");
    dot_graph<<"digraph example{\n";
    for(int i=0;i<state.size();i++){
        for(int j=0;j<state[i]->out_state.size();j++)
        dot_graph<<state[i]->state_id<<"->"<<state[i]->out_state[j]->state_id<<endl;
    }
    for(int i=0;i<state.size();i++){
        if (state[i]->identifier>=0) dot_graph<<state[i]->state_id<<" [ label = \""<< string(1,char(state[i]->identifier))<<"\"";
        else dot_graph<<state[i]->state_id<<" [ label = \"init\"";
        if (state[i]->is_final) dot_graph<<", style=\"filled\", fillcolor=\"chartreuse\"";
        if (state[i]->in_state.size()==0) dot_graph<<", shape=\"record\"";
        dot_graph<<"]"<<endl;
    }
    dot_graph<<"}";
    return;
}
#endif