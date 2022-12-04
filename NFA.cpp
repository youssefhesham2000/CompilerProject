//
// Created by Abdallah on 12/4/2022.
//

#include <cassert>
#include "NFA.h"

std::map<char, std::vector<NFANode>> NFA::getTransitionTable() const {
    return transitionTable;
}

NFA::NFA(RegExp regExp) {

}



// THOMPSON CONSTRUCTION HELPERS
NFA constructConcatenation(RegExp regExp){
    assert(regExp.type == RegExpType::concatenation);

    // first operand
    NFA nfa = NFA(regExp.operands[0]);

    // remaining operands
    for (RegExp operand: regExp.operands) {
        NFA nfa = NFA(operand);

    }
    return nfa;
}
