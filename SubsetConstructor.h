//
// Created by Abdallah on 12/6/2022.
//

#ifndef COMPILERPROJECT_SUBSETCONSTRUCTOR_H
#define COMPILERPROJECT_SUBSETCONSTRUCTOR_H


#include <set>
#include <queue>
#include "NFA.h"
#include "DFANode.h"

using NodeSet = std::set<NFANode*>;
class SubsetConstructor {
    static NodeSet getKleeneClosure(NFANode* start);
    static NodeSet getKleeneClosure(std::set<NFANode *> start);

public:
    static DFANode* construct(NFA nfa);


};


#endif //COMPILERPROJECT_SUBSETCONSTRUCTOR_H
