//
// Created by Abdallah on 12/6/2022.
//

#include "SubsetConstructor.h"


NodeSet SubsetConstructor::getKleeneClosure(NFANode* start){
    std::queue<NFANode*> q;
    NodeSet result;
    q.push(start);
    while(!q.empty()) {
        NFANode* node = q.front();q.pop();

        for (NFANode* neighbour: node->transitions[epsilonTransition]){
            if (result.count(neighbour) == 0){
                result.insert(neighbour);
                q.push(neighbour);
            }
        }
    }
    return result;
}

NodeSet SubsetConstructor::getKleeneClosure(NodeSet start){
    NodeSet result;
    for (auto node: start) {
        auto subKleeneClosure = getKleeneClosure(node);
        result.insert(subKleeneClosure.begin(), subKleeneClosure.end());
    }
    return result;
}

DFA SubsetConstructor::construct(NFA nfa){
    // counts the number of sets found, for utility
    int counter = 0;

    std::map<NodeSet, std::map<char, NodeSet>> transitionTable;
    std::queue<NodeSet> q;


    auto initKleeneClosure = getKleeneClosure(nfa.startNode);
    q.push(initKleeneClosure);


    while(!q.empty()){
        auto s = q.front(); q.pop();

        /*
            for every node in the set
                for every transition this node has
                    for all the nodes this transition goes to
                        add the node to the set
        */
        for (NFANode* node: s) {
            for (auto transitions: node->transitions) {
                char c = transitions.first;

                for (NFANode* neighbour: transitions.second) {
                    auto closure = getKleeneClosure(neighbour);
                    transitionTable[s][c].insert(closure.begin(), closure.end());
                }
            }
        }

        // Check if we have formed a new set and push it to the queue
        for (auto& x: transitionTable[s]) {
            NodeSet n = x.second;
            if (transitionTable.find(n) == transitionTable.end()){
                q.push(n);
            }
        }
    }

    // TODO: convert the transitionTable to DFANodes and connect them to each other
    throw std::runtime_error("Not implemented");
}
