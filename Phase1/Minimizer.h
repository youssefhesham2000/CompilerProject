#ifndef COMPILERPROJECT_MINIMIZER_H
#define COMPILERPROJECT_MINIMIZER_H

#include "DFA.h"

using std::vector;
using std::pair;
using std::map;
using std::string;

class Minimizer {
private:
    vector<vector<pair<int, char>>> adjacencyList;
    map<int, DFANode*> node;
    map<int, bool> visited;
    map<int, bool> isFinal;
    map<int, string> type;
    void dfs(int nodeId);
    void traverse(DFANode* currentNode, vector<vector<DFANode*>>& initialSets);

    bool areEquivalent(vector<vector<DFANode*>> v1, vector<vector<DFANode*>> v2);
    bool sameTransitions(DFANode* node1, DFANode* node2);
    vector<vector<DFANode*>> getInitialSets(DFA* dfa);
    vector<vector<DFANode*>> getNextSets(const vector<vector<DFANode*>>& currentSets);
    int getSetIndex(DFANode* dfaNode, vector<vector<DFANode*>> sets);

    DFA* constructDFA(vector<vector<DFANode*>>);

public:
    DFA* minimize(DFA* dfa);
};


#endif //COMPILERPROJECT_MINIMIZER_H
