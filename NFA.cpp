//
// Created by Abdallah on 12/4/2022.
//

#include <cassert>
#include "NFA.h"

std::map<char, std::vector<NFANode>> NFA::getTransitionTable() const {
    return transitionTable;
}

NFA::NFA(RegExp regExp) {
    switch (regExp.type) {
        case concatenation:

    }
}



// THOMPSON CONSTRUCTION HELPERS
NFA constructConcatenation(RegExp regExp){
    assert(regExp.type == RegExpType::concatenation);

    for (RegExp operand: regExp.operands) {

    }
}
