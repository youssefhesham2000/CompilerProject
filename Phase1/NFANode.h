//
// Created by Abdallah on 12/4/2022.
//
#include <vector>
#include <string>
#include <map>
#include "Pattern.h"

#ifndef COMPILERPROJECT_NFANODE_H
#define COMPILERPROJECT_NFANODE_H

const char epsilonTransition = '\0';

class NFANode {
public:
    std::vector<pair<Pattern, std::vector<NFANode*>>> transitions;
    bool isFinal;
    std::string type; // int, id, num, ...


    int getTransitionIdx(Pattern);
    void addTransition(Pattern, std::vector<NFANode*>);
    void addTransition(Pattern, NFANode*);
};


#endif //COMPILERPROJECT_NFANODE_H
