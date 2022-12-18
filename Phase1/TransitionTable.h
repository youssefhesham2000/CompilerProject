#ifndef COMPILERPROJECT_TRANSITIONTABLE_H
#define COMPILERPROJECT_TRANSITIONTABLE_H

#include "DFANode.h"

class TransitionTable {
private:
public:
    void addState(DFANode* node);
    std::map<int, std::map<char, int>> table;
    void print();
};

#endif //COMPILERPROJECT_TRANSITIONTABLE_H
