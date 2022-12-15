//
// Created by Abdallah on 12/6/2022.
//

#include <iostream>
#include "SubsetConstructor.h"
#include "RulesParser.h"


NodeSet SubsetConstructor::getKleeneClosure(NFANode* start){
    static std::unordered_map<NFANode*, NodeSet> cachedResults;
    if (cachedResults.find(start) != cachedResults.end())
        return cachedResults[start];

    std::queue<NFANode*> q;
    NodeSet result;
    q.push(start);
    result.insert(start);
    while(!q.empty()) {
        NFANode* node = q.front();q.pop();

        for (NFANode* neighbour: node->transitions[node->getTransitionIdx(Pattern())].second){
            if (result.count(neighbour) == 0){
                result.insert(neighbour);
                q.push(neighbour);
            }
        }
    }

    cachedResults[start] = result;
    return result;
}

NodeSet SubsetConstructor::getKleeneClosure(NodeSet start){
    static std::map<NodeSet, NodeSet> cachedResults;
    if (cachedResults.find(start) != cachedResults.end())
        return cachedResults[start];

    NodeSet result;
    for (auto node: start) {
        auto subKleeneClosure = getKleeneClosure(node);
        result.insert(subKleeneClosure.begin(), subKleeneClosure.end());
    }

    cachedResults[start] = result;
    return result;
}

void addTransitionHelper(NodeSet& from, const Pattern& p, NodeSet& to, std::map<NodeSet, std::vector<pair<Pattern, NodeSet>>> &transitionTable) {
    for (auto &transition: transitionTable[from]){
        if (transition.first == p) {
            transition.second.insert(to.begin(), to.end());
            return;
        }
    }

    transitionTable[from].emplace_back(p, to);
}


DFANode * SubsetConstructor::construct(NFA nfa, RulesParser parser) {

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
                Pattern p = transitions.first;

                auto closure = getKleeneClosure(NodeSet(transitions.second.begin(), transitions.second.end()));

                for (char c: p.getMatches()) {
                    transitionTable[s][c].insert(closure.begin(), closure.end());
                }
            }
        }

        // Check if we have formed a new set and push it to the queue
        for (auto x: transitionTable[s]) {
            NodeSet n = x.second;
            if (transitionTable.find(n) == transitionTable.end()){
                q.push(n);
            }
        }
    }

    std::map<NodeSet, DFANode*> setToNode;

    // Create a DFANode for each NodeSet
    std::unordered_set<string> keywords(parser.keyWords.begin(), parser.keyWords.end());
    int id = 0;
    for (auto row: transitionTable) {
        DFANode* node = new DFANode();
        node->id = id++;

        NodeSet nodeSet = row.first;
        for (NFANode* n: nodeSet){
            if (n->isFinal){
                if (node->type == "" || keywords.count(n->type))
                node->type = n->type;
                node->isFinal = true;
            }
        }
        setToNode[row.first] = node;
    }

    // Connect the DFANodes with each other
    for (auto row: transitionTable) {
        DFANode* src = setToNode[row.first];
        for (auto transition: row.second) {
            char c = transition.first;
            DFANode* dest = setToNode[transition.second];
            src->transitions[c] = dest;
        }
    }


    DFANode* startNode = setToNode[initKleeneClosure];
    return startNode;
}


