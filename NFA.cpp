//
// Created by Abdallah on 12/4/2022.
//

#include <cassert>
#include "NFA.h"
#include "NFANode.h"


/**
 * Given a regExp and the name of the token it accepts, returns an NFA with the
 * endNode (isFinal = true, type = type)
 * @param regExp
 * @param type name of the token it accepts e.g. id, num, digits
 */
NFA::NFA(RegExp regExp, std::string type) {
    NFA nfa = constructNFA(regExp);
    startNode = nfa.startNode;
    endNode = nfa.endNode;
    endNode.isFinal = true;
    endNode.type = type;
}

/**
 * Creates an NFA but all the nodes are non final
 * Used for generating intermediate NFAs that don't map to final token
 * @param regExp
 * @return
 */
NFA NFA::constructNFA(RegExp regExp){
    switch (regExp.type) {
        case terminal:
            return NFA(regExp.terminal);
        case concatenation:
            return constructConcatenation(regExp);
        default:
            throw std::runtime_error("Something went wrong");
    }
}


NFA::NFA(char c){
    startNode.transitions[c].push_back(endNode);
}

// THOMPSON CONSTRUCTION HELPERS
NFA NFA::constructConcatenation(RegExp regExp){
    assert(regExp.type == RegExpType::concatenation);

    // first operand
    NFA combinedNFA = constructNFA(regExp.operands[0]);

    // remaining operands
    for (int i = 1;i < regExp.operands.size();i++) {
        NFA nfa = constructNFA(regExp.operands[i]);
        combinedNFA.endNode.transitions[epsilonTransition].push_back(nfa.startNode);
    }
    return combinedNFA;
}


