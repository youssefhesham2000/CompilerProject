//
// Created by Abdallah on 12/4/2022.
//
#include <map>
#include <vector>
#include "NFANode.h"
#include "RegExp.h"

#ifndef COMPILERPROJECT_NFA_H
#define COMPILERPROJECT_NFA_H


class NFA {


public:
    static const char epsilonTransition = '\0';
    NFANode startNode;
    // used to mark the end of the machine, used for the thompson construction operations.
    // isFinal + type on each NFANode will mark what kind of token it accepts.
    NFANode endNode;
    explicit NFA(RegExp regExp);
    // Generate a transition table by traversing this NFA starting from startNode
    // used in subset construction
    std::map<char, std::vector<NFANode>> getTransitionTable();
};


#endif //COMPILERPROJECT_NFA_H
