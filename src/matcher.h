#include "compiler.cc"

class NFA_Matcher{
public:

    NFA_Matcher(GlushKov_NFA *nfa){
        this->nfa = nfa;
        init_table();
    }

    GlushKov_NFA *nfa;

    int state_num;
    int transition_num;
    u8 *states; // bit-state array
    u8 *final_states; // bit-arrary mark final states
    int *begin_index_of_states; // index of the first state in each kind of identifier
    int *pre_states; // array that stores the prior states to each state
    int *begin_index_of_pre; // index of the first pre state of each state

    void init_table(); // only called once in constrcter
    vector<int> naive_matcher(u8 *str, int length);
    vector<int> optimizaed_matcher(u8 *str, int length);
    vector<int> gpu_matcher(u8 *str, int length);

};