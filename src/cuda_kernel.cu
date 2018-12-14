#include "matcher.h"

// Considering the size of NFAs in application, each block handle a string's match individually

__global__ void matcher(u8 *states, u8 *final_states, int *begin_index_of_states, 
    int *pre_states, int *begin_index_of_pre, int state_num,
    int transition_num, u8 *str, int length, bool *matcher_result){
    int thread_idx = threadIdx.x;
    int block_idx = blockIdx.x;
    int thread_cnt = blockDim.x;
    int block_cnt = gridDim.x;

    int ind = 0, ch;
    int from, to;
    int pre_from, pre_to;

    __shared__ u8 shared_state[2][(state_num-1)/(8*sizeof(u8)) + 1];
    __shared__ u8 shared_final_states[(state_num-1)/(8*sizeof(u8)) + 1];

    for(int i = thread_idx; i < (state_num-1)/(8*sizeof(u8)) + 1; i+=thread_cnt){
        shared_state[1][i] = states[i];
        shared_final_states[i] = final_states[i];
    }
    __syncthreads();

    while(ind<length){
        ch = str[ind];
        from = begin_index_of_states[ch];
        if (ch<255) to = begin_index_of_states[ch+1];
        else to = state_num;

        for(int i = thread_idx+from; i<to; i+=thread_cnt){
            pre_from = begin_index_of_pre[i];
            if (i<state_num-1) pre_to = begin_index_of_pre[i+1];
            else pre_to = transition_num;
            int tmp = 0;
            for(int j=pre_from; j<pre_to; j++){
                tmp |= (shared_state[(ind+1)%2][pre_states[j]/(sizeof(u8)*8)] & (1<<(pre_states[j]%(sizeof(u8)*8))));
            }
            if(tmp) shared_state[ind%2][pre_states[j]/(sizeof(u8)*8)] |= (1<<(pre_states[j]%(sizeof(u8)*8))); // should be done with atomic operations
        }
        __syncthreads();
        for(int i = thread_idx; i < (state_num-1)/(8*sizeof(u8)) + 1; i+=thread_cnt){
            shared_state[(ind+1)%2][i] = 0;
        }
        __syncthreads();
        ind+=1;
    }
    ind -= 1;
    for(int i = thread_idx; i < (state_num-1)/(8*sizeof(u8)) + 1; i+=thread_cnt){
        if (shared_state[ind%2][i]&  shared_final_states[i]) {*matcher_result = true;}
    }
    __syncthreads();
    return;
}


vector<int> NFA_Matcher::gpu_matcher(u8 *str, int length){
    vector<int> ret;
    ret.clear();

    u8 *d_states;
    u8 *d_final_states;
    int *d_begin_index_of_states;
    int *d_pre_states;
    int *d_begin_index_of_pre;

    cudaMalloc((void **)&d_states, , );

    return ret;
}
