//
// Created by mohamed on 12/4/2022.
//
#include "NFANode.h"
#include "NFAConvertor.h"

std::set<NFANode> NFAConvertor::getEpsilonClosure(NFANode nfaNode) {
    std::set<NFANode> epsilonClosure;
    std::vector<NFANode> nodes = nfaNode.transitions.find(epsilonTransition)->second;
    for (NFANode currentNode: nodes) {
        epsilonClosure.insert(currentNode);
    }
}