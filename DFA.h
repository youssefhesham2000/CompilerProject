//#include <string>
//#include <vector>
//#include "DFANode.h"
//#include "TransitionTable.h"
//#include "Token.h"
//
//#ifndef COMPILERPROJECT_DFA_H
//#define COMPILERPROJECT_DFA_H
//
//class DFA{
//private:
//    TransitionTable transitionTable;
//    void traverse(const DFANode& node, std::map<int, bool>& visited);
//public:
//    DFA();
//    explicit DFA(const DFANode& startNode);
//    DFANode startNode;
//    std::map<int, std::map<char, int>> getTransitionTable() const;
//    std::vector<Token> accept(std::string str);
//};
//
//#endif