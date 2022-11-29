#include <string>
#include <vector>
#include "DFANode.h"
#include "TransitionTable.h"
#include "Token.h"

#ifndef COMPILERPROJECT_DFA_H
#define COMPILERPROJECT_DFA_H

class DFA{
private:
    DFANode startNode;
    TransitionTable transitionTable;
    void traverse(const DFANode& node, std::map<int, bool>& visited);
public:
    explicit DFA(const DFANode& startNode);
    std::map<int, std::map<char, int>> getTransitionTable() const;
    std::vector<Token> accept(std::string str);
};

#endif