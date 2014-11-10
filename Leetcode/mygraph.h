//
//  mygraph.h
//  Leetcode
//
//  Created by Wendi Lu on 11/3/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mygraph_h
#define Leetcode_mygraph_h


struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};




UndirectedGraphNode *clone(UndirectedGraphNode *node, unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> &copied);

UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {//Clone Graph
    if(node == nullptr) return node;
    unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> copied;
    return clone(node, copied);
}

UndirectedGraphNode *clone(UndirectedGraphNode *node, unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> &copied){
    if(copied.find(node) != copied.end()){
        return copied[node];
    }
    UndirectedGraphNode *new_node = new UndirectedGraphNode(node->label);
    copied[node] = new_node;
    for(auto nbr : node->neighbors)
        new_node->neighbors.push_back(clone(nbr, copied));
    return new_node;
}
#endif
