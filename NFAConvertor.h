//
// Created by mohamed on 12/4/2022.
//

#ifndef COMPILERPROJECT_NFACONVERTOR_H
#define COMPILERPROJECT_NFACONVERTOR_H


#include <set>
#include "DFANode.h"
#include "NFANode.h"
#include "NFA.h"
#include <map>

class NFAConvertor {
private:

    // Map of epsilon closure into DFA states.
    std::map<std::set<NFANode*>, DFANode> stateToDfa;

    /**
     *
     * @param nfaNode NFANode
     * @return set<NFANode>: set of the epsilon clousre of the given node.
     */
    std::set<NFANode*> getEpsilonClosure(NFANode* nfaNode);

    /**
     *
     * @param nfaNodes set of  NFANode
     * @param in char
     * @return Returns the new state of the NFANodes.
     */
    std::set<NFANode*> move(std::set<NFANode*> nfaNodes , char inputSymbol);

public:
    /**
     *
     * @param startNode  :NFANode
     * @return DFANode: returns the initial state of the DFA to be constructed in using DFA constructor.
     */
    DFANode convert(NFANode* startNode);
};


#endif //COMPILERPROJECT_NFACONVERTOR_H
