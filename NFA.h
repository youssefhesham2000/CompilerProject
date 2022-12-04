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
private:

    // Thompson construction helpers
    static NFA constructNFA(RegExp regExp);
    /**
     * Terminal constructor
     */
    NFA(char);
    static NFA constructConcatenation(RegExp regExp);

public:
    NFA(RegExp regExp, std::string type);

    NFANode startNode;
    // used to mark the end of the machine, used for the thompson construction operations.
    // isFinal + type on each NFANode will mark what kind of token it accepts.
    NFANode endNode;
};


#endif //COMPILERPROJECT_NFA_H
