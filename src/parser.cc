#ifndef PARSER_CC
#define PARSER_CC

#include "parser.h"

AST::AST(char *regex, int length){
    vector<int> extended_regex = extend_regex(regex, length);
    vector<int> post_exp = re2post(extended_regex);
    constructAST(post_exp);
    return;
}

void AST::constructAST(vector<int> post_regex){
    stack<ast_node *> S;
    root = nullptr;
    for(int i=0;i<post_regex.size();i++){
        struct ast_node* cur = new ast_node((post_regex[i]>=0), 
                    (post_regex[i]<0?post_regex[i]:-1), (post_regex[i]>=0?post_regex[i]:-1));
        if (cur->node_type==0){
            switch (cur->op_type){
                case KLEEN_STAR:
                    assert(!S.empty());
                    cur->child.push_back(S.top());
                    S.pop();
                    S.push(cur);
                    break;
                case ALTERNATE:
                    assert(S.size()>=2);
                    cur->child.push_back(S.top());
                    S.pop();
                    cur->child.push_back(S.top());
                    S.pop();
                    swap(cur->child[0], cur->child[1]);
                    S.push(cur);
                    break;
                case CONCATENATION:
                    assert(S.size()>=2);
                    cur->child.push_back(S.top());
                    S.pop();
                    cur->child.push_back(S.top());
                    S.pop();
                    swap(cur->child[0], cur->child[1]);
                    S.push(cur);
                    break;
                default:
                    printf("ast construction failed\n");
                    exit(-3);
                    break;
            }
        }
        else{
            S.push(cur);
        }
    }
    assert(S.size()==1);
    root = S.top();
    return;
}

// -5: concate, -4:alternate, -3: kleene star
vector<int> AST::re2post(vector<int> re){
    vector<int> ret;
    ret.clear();

    stack<int> S;

    for(int i=0 ; i<re.size(); i++){
        int ch = re[i];
        switch(ch){
            // larger number ==> higher priority
            // (, ): -1, -2
            // *: -3
            // |: -4
            // .: -5
            // char: >=0
            case LEFT_BRACKET: // ( : -1
                S.push(LEFT_BRACKET);
                break;
            case RIGHT_BRACKET:// ) : -2
                while(!S.empty()){
                    if(S.top() == LEFT_BRACKET ) break;
                    ret.push_back(S.top());
                    S.pop();
                }
                if (S.empty()) {printf("invalid regex\n"); exit(-1);}
                S.pop();
                break;
            case KLEEN_STAR: // *: -3
                if(S.empty()) {S.push(KLEEN_STAR);}
                else if (S.top()==LEFT_BRACKET){
                    S.push(KLEEN_STAR);
                }
                else if(S.top()>=KLEEN_STAR) {
                    while(!S.empty()){
                        if (S.top()<KLEEN_STAR || S.top()==LEFT_BRACKET) break;
                        ret.push_back(S.top());
                        S.pop();
                    }
                    S.push(KLEEN_STAR);
                }
                else{S.push(KLEEN_STAR);}
                break;
            case ALTERNATE: // |: -4
                if(S.empty()) {S.push(ALTERNATE);}
                else if (S.top()==LEFT_BRACKET){
                    S.push(ALTERNATE);
                }
                else if(S.top()>=ALTERNATE) {
                    while(!S.empty()){
                        if (S.top()<ALTERNATE || S.top()==LEFT_BRACKET) break;
                        ret.push_back(S.top());
                        S.pop();
                    }
                    S.push(ALTERNATE);
                }
                else{S.push(ALTERNATE);}
                break;
            case CONCATENATION:
                if(S.empty()) {S.push(CONCATENATION);}
                else if (S.top()==LEFT_BRACKET){
                    S.push(CONCATENATION);
                }
                else if(S.top()>=CONCATENATION) {
                    while(!S.empty()){
                        if (S.top()<CONCATENATION || S.top()==LEFT_BRACKET) break;
                        ret.push_back(S.top());
                        S.pop();
                    }
                    S.push(CONCATENATION);
                }
                else{S.push(CONCATENATION);}
                break;
            default:
                ret.push_back(ch);
                break;
        }
    }

    while(!S.empty()){
        if (S.top() == LEFT_BRACKET) {printf("invalid regex\n"); exit(-2);}
        ret.push_back(S.top());
        S.pop();
    }

    return ret;
}

vector<int> AST::extend_regex(char *regex, int length){
    vector<int> re;
    re.clear();

    for(int i=0; i<length; i++){
        switch(regex[i]){
            // (:-1 ):-2  *:-3 |:-4 .:-5
            case '(':
                if (re.size()){
                    int last = re[re.size()-1];
                    if (last==RIGHT_BRACKET || last==KLEEN_STAR || last>=0)
                        re.push_back(CONCATENATION);
                }
                re.push_back(LEFT_BRACKET);
                break;
            case ')':
                re.push_back(RIGHT_BRACKET);
                break;
            case '*':
                re.push_back(KLEEN_STAR);
                break;
            case '|':
                re.push_back(ALTERNATE);
                break;
            default:
                if (re.size()){
                    int last = re[re.size()-1];
                    if(last>=0 || last==RIGHT_BRACKET || last == KLEEN_STAR) re.push_back(CONCATENATION);
                }
                re.push_back(int((u8)(regex[i])));
                break;
        }
    }
    return re;
}

void AST::traverse(){
    //BFS
    queue<ast_node *> Q;
    ofstream dot_graph;
    dot_graph.open("graph.dot");
    Q.push(root);
    vector<int> src;
    vector<int> dst;
    vector<string> des;
    int cnt = 0;
    // label ids
    while(!Q.empty()){
        ast_node *cur = Q.front();
        cur->ids = cnt++;
        Q.pop();
        for(int i=0;i<cur->child.size();i++)
            Q.push(cur->child[i]);
    }

    Q.push(root);
    while(!Q.empty()){
        ast_node *cur = Q.front();
        if (cur->node_type==1)
            des.push_back(string(1,char(cur->identifier)));
        else {
            if (cur->op_type==KLEEN_STAR)
                des.push_back("*");
            if (cur->op_type==ALTERNATE)
                des.push_back("|");
            if (cur->op_type==CONCATENATION)
                des.push_back(".");
        }
        Q.pop();
        for(int i=0;i<cur->child.size();i++)
            Q.push(cur->child[i]);
        for(int i=0;i<cur->child.size();i++)
        {
            src.push_back(cur->ids);
            dst.push_back(cur->child[i]->ids);
        }
    }

    dot_graph<<"digraph example{\n";
    for(int i=0;i<src.size();i++)
        dot_graph<<to_string(src[i])<<" -> "<<to_string(dst[i])<<endl;
    
    for(int i=0;i<des.size();i++)
        dot_graph<<" "<<to_string(i)<<"[ label = \""<<des[i]<<"\"]"<<endl;
    dot_graph<<"}";
}
#endif