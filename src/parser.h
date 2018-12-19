#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

#define LEFT_BRACKET -1
#define RIGHT_BRACKET -2
#define KLEEN_STAR -3
#define CONCATENATION -4
#define ALTERNATE -5


using namespace std;



typedef unsigned char u8;

struct edge_pair{
    edge_pair(int a, int b){
        src_ids = a;
        dst_ids = b;
    }
    int src_ids;
    int dst_ids;
    bool operator == (edge_pair &a){
        return (a.src_ids == this->src_ids && a.dst_ids == this->dst_ids);
    }
};

struct ast_node{
    ast_node(int nt, int ot, int idt) {
        node_type = nt;
        op_type = ot;
        identifier = idt;
        child.clear();
        _Prefix_set.clear();
        _Suffix_set.clear();
        _Neighbor_set.clear();
    }
    int node_type; // 0: internal node or 1: leaf, -1: by default at initialization stage
    int op_type; // if node_type is internal node, then op_type is valid. -4: concate, -5: alternate, -3: kleene star
                    // we only support 3 types, for the construction of a glushkov NFA.
    int identifier; // if node_type is leaf, then identifier is valid, represent a character.
    int ids; // helper attribute for traverse in debug
    vector<ast_node *> child;
    // Used in Compiler
    bool _V_set;
    vector<int> _Prefix_set;
    vector<int> _Suffix_set;
    vector<edge_pair> _Neighbor_set;
};

class AST{
public:
    AST(char *regex, int length); // construct ast from original regular expression
    struct ast_node * root;
    vector<int> re2post(vector<int> re);
    vector<int> extend_regex(char *regex, int length); // extend user's regex input to standard regex (with .)
    void constructAST(vector<int> post_regex);
    void traverse();

};
#endif