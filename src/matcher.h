#include "compiler.cc"

class NFA_Matcher{
public:

    NFA_Matcher(GlushKov_NFA *nfa){
        this->nfa = nfa;
    }

    GlushKov_NFA *nfa;

    vector<int> naive_matcher(u8 *str, int length);
    vector<int> gpu_matcher(u8 *str, int length);

};