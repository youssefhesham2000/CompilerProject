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
    std::map<char, std::vector<NFANode>> transitionTable;

public:
    static const char espilon = '\0';
    NFANode startNode;
    // used to mark the end of the machine, used for the thompson construction operations.
    // isFinal + type on each NFANode will mark what kind of token it accepts.
    NFANode endNode;
    explicit NFA(RegExp regExp);
    std::map<char, std::vector<NFANode>> getTransitionTable() const;
};


#endif //COMPILERPROJECT_NFA_H