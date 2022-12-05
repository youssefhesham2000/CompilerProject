//
// Created by mohamed on 12/4/2022.
//
#include "NFANode.h"
#include "NFAConvertor.h"
#include <stack>

DFANode NFAConvertor::convert(NFANode* startNode) {
    //Get the first state.
    std::set<NFANode*> firstState = this->getEpsilonClosure(startNode);
    std::vector<char> terminals;
    std::stack<std::set<NFANode*>> stack;

    // Initialize the stack with the first state.
    stack.push(firstState);

    int stateCounter = 0;
    DFANode startDfaNode;
    startDfaNode.id = stateCounter;
    std::set<std::set<NFANode*>> visited={};
    // Add the first state to the state mapper.
    this->stateToDfa.insert({firstState, startDfaNode });
    stateCounter++;
    while (!stack.empty()) {

        std::set<NFANode*> tempState = stack.top();
        visited.insert(tempState);

        // Get all the valid inputs (terminals ) to this state.
        for(auto node: tempState) {
            for(const auto it: node->transitions ) {
               terminals.push_back(it.first);
            }
        }

        std::map<char, std::set<NFANode*>> stateCharToStateMap;

        for(auto terminal: terminals) {
            if (terminal != epsilonTransition) {
                std::set<NFANode*> nextState = this->move(tempState, terminal);
                stateCharToStateMap.insert({terminal, nextState});
                stack.pop();
                if (!visited.count(nextState)) {
                    // new state.
                    stack.push(nextState);
                }
            }
        }
        terminals.clear();
        DFANode tempDfaNode = stateToDfa.find(tempState)->second;
        for(auto iterator: stateCharToStateMap) {

            if (!stateToDfa.count(iterator.second)) {
                DFANode tempNode;
                tempNode.id = stateCounter;
                stateCounter++;
                stateToDfa.insert({iterator.second, tempNode});
            }
            tempDfaNode.transitions.insert({iterator.first, stateToDfa.find(iterator.second)->second});
        }

        for(auto iterator: tempState) {
            if(iterator->isFinal){
                tempDfaNode.isFinal= true;
                tempDfaNode.type = iterator->type;
                // check with loai what is type exactly.
            }
        }
        stateToDfa.insert({tempState,tempDfaNode});

    }

    // returns the first DFANode (start state).
    return stateToDfa.find(firstState)->second;

}

std::set<NFANode*> NFAConvertor::move(std::set<NFANode*> nfaNodes, char inputSymbol) {
    std::vector<std::vector<NFANode*>> nextSateNodes;
    std::set<NFANode*> newState = {};
    // Get the next state(nodes) for each node with the given symbol.
    for (auto node : nfaNodes) {
        if (node->transitions.count(inputSymbol)){
            nextSateNodes.push_back(node->transitions.find(inputSymbol)->second);
        }
    }
    //Get the epsilon closure for each node.
    for(auto row: nextSateNodes){
        for(auto col: row){
            std::set<NFANode*> tempSet = this->getEpsilonClosure(col);
            // Get union of generated closures.
            for(auto& node: tempSet){
                newState.insert(node);
            }
        }
    }
    return newState;
}

std::set<NFANode*> NFAConvertor::getEpsilonClosure(NFANode* nfaNode) {

    std::set<NFANode*> epsilonClosure={};
    epsilonClosure.insert(nfaNode);
    if (nfaNode->isFinal){
        return epsilonClosure;
    }

    std::vector<NFANode*> nodes = nfaNode->transitions.find(epsilonTransition)->second;
    std::stack<NFANode*> stack;

    for (NFANode* element : nodes) {
        epsilonClosure.insert(element);
        stack.push(element);
    }
    while (!stack.empty()){
        NFANode* tempNode = stack.top();
        if (tempNode->transitions.count(epsilonTransition)){
            std::vector<NFANode*> tempNodes = tempNode->transitions.find(epsilonTransition)->second;

            for (NFANode* element : tempNodes) {
                // Check if the node is already visited.
                auto it = epsilonClosure.find(element);
                if (it != epsilonClosure.end()){
                    epsilonClosure.insert(element);
                    stack.push(element);
                }
            }
        }
        stack.pop();
    }
    return epsilonClosure;
}

