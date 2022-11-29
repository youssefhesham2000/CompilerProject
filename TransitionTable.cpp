#include "TransitionTable.h"

void TransitionTable::addState(const DFANode& node) {
    for(const auto& p: node.transitions) {
        char transitionChar = p.first;
        int successorId = p.second.id;
        this->table[node.id][transitionChar] = successorId;
    }
}
