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


vector<int> gpu_matcher(NFA_Matcher &nfa_mat, u8 *str, int length){
    vector<int> ret;
    ret.clear();

    u8 *d_states;
    u8 *d_final_states;
    int *d_begin_index_of_states;
    int *d_pre_states;
    int *d_begin_index_of_pre;
    bool *matcher_result = new bool;
    bool *d_matcher_result;
    *matcher_result = false;
    u8 *d_str;

    cudaMalloc((void **)&d_states, sizeof(u8)*((nfa_mat.state_num-1)/(8*sizeof(u8)) + 1));
    cudaMalloc((void **)&d_final_states, sizeof(u8)*((nfa_mat.state_num-1)/(8*sizeof(u8)) + 1));
    cudaMalloc((void **)&d_begin_index_of_states, sizeof(int)*(256));
    cudaMalloc((void **)&d_begin_index_of_pre, sizeof(int)*(nfa_mat.state_num));
    cudaMalloc((void **)&d_pre_states, sizeof(int)*(nfa_mat.transition_num));
    cudaMalloc((void **)&d_str, sizeof(u8)*length);
    cudaMalloc((void **)&d_matcher_result, sizeof(bool));

    cudaMemcpy(d_states, nfa_mat.states, sizeof(u8)*((nfa_mat.state_num-1)/(8*sizeof(u8)) + 1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_final_states, nfa_mat.final_states, sizeof(u8)*((nfa_mat.state_num-1)/(8*sizeof(u8)) + 1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_begin_index_of_states, nfa_mat.begin_index_of_states, sizeof(int)*(256), cudaMemcpyHostToDevice);
    cudaMemcpy(d_begin_index_of_pre, nfa_mat.begin_index_of_pre, sizeof(int)*(nfa_mat.state_num), cudaMemcpyHostToDevice);
    cudaMemcpy(d_pre_states, nfa_mat.pre_states, sizeof(int)*(nfa_mat.transition_num), cudaMemcpyHostToDevice);
    cudaMemcpy(d_str, str, sizeof(u8)*length, cudaMemcpyHostToDevice);
    cudaMemcpy(d_matcher_result, matcher_result, sizeof(bool), cudaMemcpyHostToDevice);
    dim3 grid(1,0,0);
    dim3 block(1024,0,0);
    matcher<<<grid, block>>>(d_states, d_final_states, d_begin_index_of_states, d_pre_states, d_begin_index_of_pre, state_num, transition_num, d_str, length, matcher_result);
    cudaDeviceSynchronize();

    if(*matcher_result) ret.push_back(length-1);
    return ret;
}
