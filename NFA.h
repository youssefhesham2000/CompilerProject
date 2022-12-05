//
// Created by Abdallah on 12/4/2022.
//
#include <map>
#include <vector>
#include "NFANode.h"
#include "RegExp.h"
#include "map"
#ifndef COMPILERPROJECT_NFA_H
#define COMPILERPROJECT_NFA_H


class NFA {
private:

    // Thompson construction helpers
    static NFA constructNFA(RegExp regExp);
    // Terminal constructor, connects the start with the end with the given char
    NFA(char);
    // Empty construction, doesn't connect the start and end nodes
    NFA(){};
    static NFA constructConcatenation(RegExp regExp);
    static NFA constructDisjunction(RegExp regExp);
    static NFA constructKleeneClosure(RegExp regExp);
    static NFA constructPositiveClosure(RegExp regExp);


public:

    NFA(RegExp regExp, std::string type);

    static NFA constructCombinedNFA(std::map<std::string,RegExp> parsedRegExp);

    NFANode* startNode = new NFANode();
    // used to mark the end of the machine, used for the thompson construction operations.
    // isFinal + type on each NFANode will mark what kind of token it accepts.
    NFANode* endNode =new NFANode();

};


#endif //COMPILERPROJECT_NFA_H
