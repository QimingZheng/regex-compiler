#include "parser.cc"

struct state_node{
    state_node(int si, int idt) {
        state_id = si;
        identifier = idt;
        is_final = false;
        in_state.clear();
        out_state.clear();
    }
    int state_id;
    int identifier;
    bool is_final;
    vector<state_node *> in_state;
    vector<state_node *> out_state;
};

class GlushKov_NFA{
public:
    GlushKov_NFA(AST *ast);
    AST *ast;
    vector<state_node *> state; // state set, final representation of NFA

    // traverse ast and label the leaf nodes' ids, initialize states
    // in the same way, store states in "state" variable.
    void label_ast_to_nfa(ast_node *_ast);
    
    bool V_set(ast_node *_ast); // V-set of ast, return true: allow empty word, false: not allow empty word
    vector<int> Prefix_set(ast_node *_ast); // Prefix-set of ast, return state_id (==ast_node.ids)
    vector<int> Suffix_set(ast_node *_ast); // Suffix-set of ast, return state_id (==ast_node.ids)
    vector<edge_pair> Neighbor_set(ast_node *_ast); // neighbor-set of ast, return edge_pair(src-state_id, dst-state_id) (==ast_node.ids)
};

template <typename T>
vector<T> vector_union(vector<T> &a, vector<T> &b);