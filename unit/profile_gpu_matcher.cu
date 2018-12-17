#include "matcher.h"
#include "cuda_kernel.cu"

int main(int argc, char **argv){
    assert(argc == 3);
    char regex[]="(qq)*|(we)rtyu(io)*p*as*df((gh)|(jkl)|(zxc)|(vbn)|(m123)|(4567)|(890q)|(wert)y*ui)op*(a*s*)dfghjklzxcvbnm";
    int length = strlen(regex);
    
    AST ast(regex, length);
    GlushKov_NFA NFA(&ast);
    
    NFA_Matcher Matcher(&NFA);

    int str_num = atoi(argv[2]);
    u8 *input_str = new u8[atoi(argv[1])];
    int *str_len = new int[str_num]
    int *str_begin_ind = new int[str_num];

    for(int i=0;i<str_num-1;i++) {
        str_len[i] = atoi(argv[1])/str_num;
        str_begin_ind = i*(atoi(argv[1])/str_num);
    }
    str_len[str_num-1] = atoi(argv[1])%str_num;
    str_begin_ind[str_num-1] = i*(atoi(argv[1])/str_num);

    tmp = gpu_matcher(Matcher.state_num, Matcher.transition_num, Matcher.states, Matcher.final_states, Matcher.begin_index_of_states,
        Matcher.begin_index_of_pre, Matcher.pre_states, str_num, input_str, str_begin_ind, &str_len);

    return 0;
}