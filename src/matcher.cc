#include "matcher.h"

#define get_bit(a) states[a/(8*sizeof(u8))]&(1<<(a%(8*sizeof(u8))))
#define set_bit(a) states[a/(8*sizeof(u8))]|=(1<<(a%(8*sizeof(u8))))
#define _set_bit(a) final_states[a/(8*sizeof(u8))]|=(1<<(a%(8*sizeof(u8))))

vector<int> NFA_Matcher::naive_matcher(u8 *str, int length){
    vector<int> ret;
    state_node *cur = nfa->entrance;
    map <int, state_node*> Map[2]; // state_id -> state_node
    Map[1].insert(make_pair(cur->state_id, cur));
    int ind = 0;

    if (cur->is_final) ret.push_back(ind);
    
    while(ind<length){
        for(auto iter = Map[(1+ind)%2].begin(); iter!=Map[(1+ind)%2].end(); iter++)
        {
            for(auto j = (iter->second)->out_state.begin() ; j!=(iter->second)->out_state.end() ; j++){
                if((*j)->identifier!=int(str[ind])) continue;
                if(Map[ind%2].find((*j)->state_id)==Map[ind%2].end())
                    Map[ind%2].insert(make_pair((*j)->state_id, (*j)));
            }
        }
        for(auto iter = Map[ind%2].begin(); iter!=Map[ind%2].end(); iter++)
        {
            if ((iter->second)->is_final){
                ret.push_back(ind);
                break;
            }
        }
        Map[(1+ind)%2].clear();
        ind += 1;
    }
    return ret;
}

vector<int> NFA_Matcher::optimizaed_matcher(u8 *str, int length){
    vector<int> ret;
    
    // clear states 
    memset(states, 0, sizeof(u8)*((state_num-1)/(8*sizeof(u8)) + 1));
    // init start states
    states[0] = 1;

    for(int i=0; i<length; i++){
        int ch = str[i];
        int from = begin_index_of_states[ch];
        int to = (ch == 255) ? state_num : begin_index_of_states[ch+1];
        vector<int> tmp;
        tmp.clear();
        for(int j=from; j<to; j++)
        {
            for (int k=begin_index_of_pre[j]; k< ((j==state_num-1)?transition_num:begin_index_of_pre[j+1]); k++){
                if (get_bit(pre_states[k])) {tmp.push_back(j); break;}
            }
        }

        for(int j=0;j<(state_num-1)/(sizeof(u8)*8)+1; j++)
            states[j]=0;
        for(int j=0;j<tmp.size(); j++)
            set_bit(tmp[j]);

        for(int j=0; j<(state_num-1)/(sizeof(u8)*8)+1;j++)
            if(final_states[j]&states[j]) {ret.push_back(i); break;}
    }

    return ret;
}

void NFA_Matcher::init_table(){

    // init state_node's identifier == -6, sort states according to their identifier
    sort(nfa->state.begin(), nfa->state.end(), [](state_node *a, state_node *b){return a->identifier < b->identifier;});

    // Attention!!!! reassign state_node's ids, and start-state's id is 0
    int cnt = 0;
    for (auto iter = nfa->state.begin(); iter != nfa->state.end(); iter++) (*iter)->state_id = cnt++;

    state_num = nfa->state.size();

    states = new u8[(state_num-1)/(8*sizeof(u8)) + 1];
    memset(states, 0, sizeof(u8)*((state_num-1)/(8*sizeof(u8)) + 1));

    begin_index_of_states = new int[256];
    memset(begin_index_of_states, 0, sizeof(int)*256);
    int _cnt = 0;

    for(auto iter = nfa->state.begin(); iter != nfa->state.end(); iter++){
        if((*iter)->identifier>_cnt) {
            for(int k = _cnt; k<(*iter)->identifier; k++)
                begin_index_of_states[k]=state_num;
            begin_index_of_states[(*iter)->identifier] = (*iter)->state_id;
            _cnt=1+(*iter)->identifier;
        }
        else if((*iter)->identifier==_cnt){
            begin_index_of_states[(*iter)->identifier] = (*iter)->state_id;
            _cnt++;
        }
    }
    for(int i=_cnt; i<256;i++)  begin_index_of_states[i]=state_num;
    
    vector<int> tmp_pre_state;
    vector<int> tmp_pre_index;

    for(auto iter = nfa->state.begin(); iter != nfa->state.end(); iter++){
        tmp_pre_index.push_back(tmp_pre_state.size());
        for(auto j = (*iter)->in_state.begin(); j!=(*iter)->in_state.end(); j++)
        {
            tmp_pre_state.push_back((*j)->state_id);
        }
    }

    transition_num = tmp_pre_state.size();
    pre_states = new int[tmp_pre_state.size()];
    begin_index_of_pre = new int[state_num];
    
    for(int i=0;i<state_num;i++) begin_index_of_pre[i] = tmp_pre_index[i];
    for(int i=0;i<tmp_pre_state.size();i++) pre_states[i] = tmp_pre_state[i];

    for(int i=0;i<state_num;i++) if(nfa->state[i]->is_final) _set_bit(i);

    return;
}