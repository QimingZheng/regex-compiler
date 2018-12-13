#include "matcher.h"

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