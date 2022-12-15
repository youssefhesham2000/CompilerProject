//
// Created by Abdallah on 12/4/2022.
//

#include "NFANode.h"

int NFANode::getTransitionIdx(Pattern pattern){

    for (int i = 0;i < transitions.size();i++) {
        if (pattern == transitions[i].first)
            return i;
    }

    // If the transition is not found, add it
    transitions.emplace_back(pattern, std::vector<NFANode*>{});
    return (int)transitions.size()-1;
}

void NFANode::addTransition(Pattern p, NFANode* node) {
    int i = getTransitionIdx(p);
    transitions[i].second.push_back(node);
}


void NFANode::addTransition(Pattern p, std::vector<NFANode*> node) {
    int i = getTransitionIdx(p);
    transitions[i].second.insert(transitions[i].second.end(), node.begin(), node.end());
}