#include "parser.h"
//#include "matcher.h"

// Considering the size of NFAs in application, each block handle a string's match individually

__global__ void matcher(u8 *states, u8 *final_states, int *begin_index_of_states, 
    int *pre_states, int *begin_index_of_pre, int state_num,
    int transition_num, u8 *str, int length, bool *matcher_result){
    int thread_idx = threadIdx.x;
    //int block_idx = blockIdx.x;
    int thread_cnt = blockDim.x;
    //int block_cnt = gridDim.x;

    int ind = 0, ch;
    int from, to;
    int pre_from, pre_to;

    //__shared__ u8 shared_state[2][(state_num-1)/(8*sizeof(u8)) + 1];
    //__shared__ u8 shared_final_states[(state_num-1)/(8*sizeof(u8)) + 1];

    __shared__ int shared_state[2][1<<10]; // state num should be less than 32K
    __shared__ int shared_final_states[1<<10]; // state num should be less than 32K

    for(int i = thread_idx; i < (state_num-1)/(8*sizeof(int)) + 1; i+=thread_cnt){
        shared_state[0][i] = 0;
        shared_state[1][i] = (int(states[4*i])) | (int(states[4*i+1])<<8) | (int(states[4*i+2])<<16) | (int(states[4*i+3])<<24);
        shared_final_states[i] = (int(final_states[4*i])) | (int(final_states[4*i+1])<<8) | (int(final_states[4*i+2])<<16) | (int(final_states[4*i+3])<<24);
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
                tmp |= (shared_state[(ind+1)%2][pre_states[j]/(sizeof(int)*8)] & (1<<(pre_states[j]%(sizeof(int)*8))));
            }
            if(tmp) atomicOr(&shared_state[ind%2][i/(sizeof(int)*8)], (1<<(i%(sizeof(int)*8)))); // should be done with atomic operations
        }
        __syncthreads();
        for(int i = thread_idx; i < (state_num-1)/(8*sizeof(int)) + 1; i+=thread_cnt){
            shared_state[(ind+1)%2][i] = 0;
        }
        __syncthreads();
        ind+=1;
    }
    ind -= 1;
    for(int i = thread_idx; i < (state_num-1)/(8*sizeof(int)) + 1; i+=thread_cnt){
        if (shared_state[ind%2][i] & shared_final_states[i]) {*matcher_result = true;}
    }
    __syncthreads();
    return;
}


vector<int> gpu_matcher(int state_num, int transition_num, u8 *states, u8 *final_states, int *begin_index_of_states,
    int *begin_index_of_pre, int *pre_states, u8 *str, int length){
    vector<int> ret;
    ret.clear();

    states[0] = 1;

    u8 *d_states;
    u8 *d_final_states;
    int *d_begin_index_of_states;
    int *d_pre_states;
    int *d_begin_index_of_pre;
    bool *matcher_result = new bool;
    bool *d_matcher_result;
    *matcher_result = false;
    u8 *d_str;

    cudaMalloc((void **)&d_states, sizeof(u8)*((state_num-1)/(8*sizeof(u8)) + 1));
    cudaMalloc((void **)&d_final_states, sizeof(u8)*((state_num-1)/(8*sizeof(u8)) + 1));
    cudaMalloc((void **)&d_begin_index_of_states, sizeof(int)*(256));
    cudaMalloc((void **)&d_begin_index_of_pre, sizeof(int)*(state_num));
    cudaMalloc((void **)&d_pre_states, sizeof(int)*(transition_num));
    cudaMalloc((void **)&d_str, sizeof(u8)*length);
    cudaMalloc((void **)&d_matcher_result, sizeof(bool));

    cudaMemcpy(d_states, states, sizeof(u8)*((state_num-1)/(8*sizeof(u8)) + 1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_final_states, final_states, sizeof(u8)*((state_num-1)/(8*sizeof(u8)) + 1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_begin_index_of_states, begin_index_of_states, sizeof(int)*(256), cudaMemcpyHostToDevice);
    cudaMemcpy(d_begin_index_of_pre, begin_index_of_pre, sizeof(int)*(state_num), cudaMemcpyHostToDevice);
    cudaMemcpy(d_pre_states, pre_states, sizeof(int)*(transition_num), cudaMemcpyHostToDevice);
    cudaMemcpy(d_str, str, sizeof(u8)*length, cudaMemcpyHostToDevice);
    cudaMemcpy(d_matcher_result, matcher_result, sizeof(bool), cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block(1024,1,1);
    matcher<<<grid, block>>>(d_states, d_final_states, d_begin_index_of_states, d_pre_states, d_begin_index_of_pre,
            state_num, transition_num, d_str, length, d_matcher_result);
    cudaDeviceSynchronize();

    cudaMemcpy(matcher_result, d_matcher_result, sizeof(bool), cudaMemcpyDeviceToHost);

    if(*matcher_result) ret.push_back(length-1);
    return ret;
}
