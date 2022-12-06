#include "DFA.h"

DFA::DFA() {}

DFA::DFA(DFANode* startNode) {
    this->startNode = startNode;
    std::map<int, bool> visited;
    traverse(startNode, visited);
}

void DFA::traverse(DFANode* node, std::map<int, bool>& visited) {
    if(visited[node->id])
        return;
    visited[node->id] = true;
    transitionTable.addState(node);
    for(const auto& p: node->transitions){
        DFANode* successor = p.second;
        traverse(successor, visited);
    }
}

std::map<int, std::map<char, int>> DFA::getTransitionTable() const {
    return this->transitionTable.table;
}

// Currently O(n^2 log(n)), can easily be modified to be O(nlogn), maybe even O(n)...
std::vector<Token> DFA::accept(std::string str) {
    if (str == "")
        return {};

    //transitionTable.print();
    auto table = getTransitionTable();
    DFANode* currentState = startNode;
    int lastAcceptedIndex = 0;
    DFANode* lastAcceptedState;
    Token lastAcceptedToken;

    for(int i=0; i<=str.length(); i++){
        if(i == str.length() || currentState->transitions[str[i]] == nullptr) { // No more states to go to / dead state
            if(lastAcceptedState == nullptr) { // Never seen an accepted state, start error recovery mode
                return accept(str.substr(1)); //Panic mode
            }

            std::vector<Token> acceptedTokens;
            acceptedTokens.push_back(lastAcceptedToken);

            if (i != str.length()) {
                // Parse the rest of the input
                auto remainingTokens = accept(str.substr(lastAcceptedIndex + 1));
                acceptedTokens.insert(acceptedTokens.end(), remainingTokens.begin(), remainingTokens.end());
            }
            return acceptedTokens;

        } else {
            currentState = currentState->transitions[str[i]];
            if(currentState->isFinal){   // Apply maximal munch
                lastAcceptedIndex = i;
                lastAcceptedState = currentState;
                lastAcceptedToken.value = str.substr(0, i + 1);
                lastAcceptedToken.type = currentState->type;
            }
        }
    }

    return {};
}