#include "DFA.h"

DFA::DFA(const DFANode& startNode) {
    this->startNode = startNode;
    std::map<int, bool> visited;
    traverse(startNode, visited);
}

void DFA::traverse(const DFANode& node, std::map<int, bool>& visited) {
    if(visited[node.id])
        return;
    visited[node.id] = true;
    transitionTable.addState(node);
    for(const auto& p: node.transitions){
        DFANode successor = p.second;
        traverse(successor, visited);
    }
}

std::map<int, std::map<char, int>> DFA::getTransitionTable() const {
    return this->transitionTable.table;
}

// Currently O(n^2 log(n)), can easily be modified to be O(nlogn), maybe even O(n)...
std::vector<Token> DFA::accept(std::string str) {
    auto table = getTransitionTable();
    DFANode currentState = startNode;
    int lastAcceptedIndex = 0;
    DFANode lastAcceptedState;
    Token lastAcceptedToken;

    for(int i=0; i<=str.length(); i++){
        if(i == str.length() || table.find(currentState.id) == table.end()) { // No more states to go to / dead state
            if(lastAcceptedState.isFinal) { // Never seen an accepted state, start error recovery mode
                return accept(str.substr(1)); //Panic mode
            }

            auto acceptedTokens = accept(str.substr(lastAcceptedIndex + 1));
            acceptedTokens.push_back(lastAcceptedToken);
            return acceptedTokens;

        } else {
            currentState = currentState.transitions[str[i]];
            if(currentState.isFinal){   // Apply maximal munch
                lastAcceptedIndex = i;
                lastAcceptedState = currentState;
                lastAcceptedToken.value = str.substr(0, i + 1);
                lastAcceptedToken.type = currentState.type;
            }
        }
    }

    return {};
}
