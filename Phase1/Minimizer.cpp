#include <iostream>
#include "Minimizer.h"

DFA* Minimizer::constructDFA(vector<vector<DFANode*>> minimizedSet){
    map<int, int> newId;
    for(int i=0; i<minimizedSet.size(); i++){
        for(auto state: minimizedSet[i]) {
            newId[state->id] = i;
            isFinal[i] |= state->isFinal;
            type[i] = (type[i].size() >= state->type.size()? type[i] : state->type);
        }
    }

    adjacencyList.resize(minimizedSet.size());
    for(int i=0; i<minimizedSet.size(); i++){
        for(auto p: minimizedSet[i][0]->transitions) {
            if(p.second == NULL)
                continue;
            char c = p.first;
            int successorId = newId[p.second->id];
            adjacencyList[i].push_back({successorId, c});
        }
    }

    DFANode* startNode = new DFANode();
    startNode->id = 0;
    startNode->isFinal = isFinal[0];
    node[0] = startNode;
    dfs(startNode->id);
    return new DFA(startNode);
}

void Minimizer::dfs(int nodeId){
    DFANode* currentNode = node[nodeId];

    for(auto p: adjacencyList[nodeId]){
        int successorId = p.first;
        char c = p.second;
        if(visited[successorId]){
            DFANode* successorNode = node[successorId];
            currentNode->transitions[c] = successorNode;
        } else {
            visited[successorId] = true;
            node[successorId] = new DFANode();
            node[successorId]->id = successorId;
            node[successorId]->isFinal = isFinal[successorId];
            node[successorId]->type = type[successorId];
            dfs(successorId);
            DFANode* successorNode = node[successorId];
            currentNode->transitions[c] = successorNode;
        }
    }
}

bool Minimizer::areEquivalent(vector<vector<DFANode*>> v1, vector<vector<DFANode*>> v2){
    if(v1.size() != v2.size())
        return false;

    for(int i=0; i<v1.size(); i++)
        if(v1[i].size() != v2[i].size())
            return false;

    return true;
}

DFA* Minimizer::minimize(DFA* dfa) {
    vector<vector<DFANode*>> previousSet;
    vector<vector<DFANode*>> currentSet = getInitialSets(dfa);
    while(!areEquivalent(previousSet, currentSet)){
        previousSet = currentSet;
        currentSet = getNextSets(currentSet);
    }
    return constructDFA(currentSet);
}

void Minimizer::traverse(DFANode* currentNode, vector<vector<DFANode*>>& initialSets){
    if(!currentNode->isFinal)
        initialSets[0].push_back(currentNode);
    else
        initialSets[1].push_back(currentNode);

    for(auto p: currentNode->transitions){
        DFANode* successor = p.second;
        if(!visited[successor->id]) {
            visited[successor->id] = true;
            traverse(successor, initialSets);
        }
    }
}

vector<vector<DFANode*>> Minimizer::getInitialSets(DFA* dfa){
    vector<vector<DFANode*>> initialSets;
    initialSets.resize(2);
    traverse(dfa->startNode, initialSets);
    visited.clear();
    return initialSets;
}

bool Minimizer::sameTransitions(DFANode* node1, DFANode* node2){
    for(auto edge: node1->transitions){
        if(edge.second == NULL && node2->transitions[edge.first] != NULL)
            return false;
        if(node2->transitions[edge.first] == NULL)
            return false;
        if(node2->transitions[edge.first]->id != edge.second->id ||
           node2->transitions[edge.first]->isFinal != edge.second->isFinal ||
           node2->transitions[edge.first]->type != edge.second->type)
            return false;
    }

    return true;
}

int Minimizer::getSetIndex(DFANode* dfaNode, vector<vector<DFANode*>> sets){
    for(int i=0; i<sets.size(); i++){
        if(sameTransitions(dfaNode, sets[i][0]) && dfaNode->type == sets[i][0]->type)
            return i;
    }

    return -1;
}

vector<vector<DFANode*>> Minimizer::getNextSets(const vector<vector<DFANode*>>& currentSets){
    vector<vector<DFANode*>> nextSets;

    for(const auto& st: currentSets){
        for(const auto& currentNode: st){
            int idx = getSetIndex(currentNode, nextSets);
            if(idx == -1){
                nextSets.push_back({currentNode});
            } else {
                nextSets[idx].push_back(currentNode);
            }
        }
    }

    return nextSets;
}