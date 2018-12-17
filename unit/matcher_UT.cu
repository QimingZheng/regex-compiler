#include "matcher.h"
#include "cuda_kernel.cu"

int main(){
    char regex[]="(asd|fns*daj)*|fsj(dav)*f(fs|da)";
    int length = strlen(regex);
    
    AST ast(regex, length);
    //ast.traverse();
    
    GlushKov_NFA NFA(&ast);
    //NFA.traverse();
    
    NFA_Matcher Matcher(&NFA);

    u8 input_str_0[] = "asfnsssdajsjdavdavffda";
    length = 22;
    int *str_begin_ind = new int;
    *str_begin_ind = 0;

    vector<int> tmp = Matcher.naive_matcher(input_str_0, length);
    cout<<tmp.size()<<endl;
    tmp = Matcher.optimized_matcher(input_str_0, length);
    cout<<tmp.size()<<endl;
    tmp = gpu_matcher(Matcher.state_num, Matcher.transition_num, Matcher.states, Matcher.final_states, Matcher.begin_index_of_states,
        Matcher.begin_index_of_pre, Matcher.pre_states, 1, input_str_0, str_begin_ind, &length);
    cout<<tmp.size()<<endl;

    u8 input_str_1[] = "fsjdavdavdavdavdavdavdavffffda";
    length = 30;
    *str_begin_ind = 0;

    tmp = Matcher.naive_matcher(input_str_1, length);
    cout<<tmp.size()<<endl;
    tmp = Matcher.optimized_matcher(input_str_1, length);
    cout<<tmp.size()<<endl;
    tmp = gpu_matcher(Matcher.state_num, Matcher.transition_num, Matcher.states, Matcher.final_states, Matcher.begin_index_of_states,
        Matcher.begin_index_of_pre, Matcher.pre_states, 1, input_str_1, str_begin_ind, &length);
    cout<<tmp.size()<<endl;

    return 0;
}