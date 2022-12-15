//
// Created by Abdallah on 12/4/2022.
//

#include <cassert>
#include <stdexcept>
#include <set>
#include <queue>
#include <iostream>
#include "NFA.h"
#include "NFANode.h"


/**
 * Given a regExp and the name of the token it accepts, returns an NFA with the
 * endNode (isFinal = true, type = type)
 * @param regExp
 * @param type name of the token it accepts e.g. id, num, digits
 */
NFA::NFA(RegExp regExp, std::string type) {
//    cout << type << " :" << endl;
//    for (string line: regExp.toString())
//        cout << line << endl;
//    cout << "----------------------------------------\n";
    NFA nfa = constructNFA(regExp);
    startNode = nfa.startNode;
    endNode = nfa.endNode;
    endNode->isFinal = true;
    endNode->type = type;
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
        case epsilon:
            return NFA(epsilonTransition);
        case concatenation:
            return constructConcatenation(regExp);
        case disjunction:
            return constructDisjunction(regExp);
        case range:
            return constructRange(regExp);
        case kleeneClosure:
            return constructKleeneClosure(regExp);
        case positiveClosure:
            return constructPositiveClosure(regExp);
        default:
            throw std::runtime_error("Something went wrong");
    }
}

/**
 *
 * @param NFAs : vector<NFA> vector of the wanted NFAs to be combined
 * @return NFA: returns a combined NFA.
 */
NFA NFA::constructCombinedNFA(std::map<std::string,RegExp> parsedRegExp) {
    std::vector<NFA> NFAs;
    for(auto item: parsedRegExp) {
        NFA tempNfa = NFA(item.second, item.first);
        NFAs.push_back(tempNfa);
    }

    NFA combinedNFA;
    // loop over the NFAs and add an epsilon transition from the combinedNFA to the start node of each.
    std::vector<NFANode*> startNodes;
    for(auto& nfa: NFAs) {
        startNodes.push_back(nfa.startNode);
    }

    combinedNFA.startNode->addTransition(Pattern(), startNodes);
    return combinedNFA;
}


NFA::NFA(char c){
    startNode->addTransition(Pattern(c), std::vector<NFANode*>{endNode});
}

// THOMPSON CONSTRUCTION HELPERS
// All these constructors don't set any isFinal on any nodes, just creates the connections
NFA NFA::constructConcatenation(RegExp regExp){
    assert(regExp.type == RegExpType::concatenation);

    // first operand
    NFA initNFA = constructNFA(regExp.operands[0]);
    NFANode* startNode = initNFA.startNode;
    NFANode* lastEndNode = initNFA.endNode;

    // remaining operands
    for (int i = 1;i < regExp.operands.size();i++) {
        NFA nfa = constructNFA(regExp.operands[i]);
        lastEndNode->addTransition(Pattern(), std::vector<NFANode*>{nfa.startNode});
        lastEndNode = nfa.endNode;
    }

    NFA nfa;
    nfa.startNode = startNode;
    nfa.endNode = lastEndNode;
    return nfa;
}

NFA NFA::constructDisjunction(RegExp regExp){
    assert(regExp.type == RegExpType::disjunction);

    NFA combinedNFA;

    for (RegExp operand: regExp.operands) {
        NFA nfa = constructNFA(operand);

        combinedNFA.startNode->addTransition(Pattern(), nfa.startNode);

        nfa.endNode->addTransition(Pattern(), combinedNFA.endNode);
    }

    return combinedNFA;
}


NFA NFA::constructRange(RegExp regExp){
    assert(regExp.type == RegExpType::range);
    Pattern p(regExp.operands.front().terminal, regExp.operands.back().terminal);

    NFA combinedNFA;
    combinedNFA.startNode->addTransition(p, combinedNFA.endNode);
    return combinedNFA;
}

NFA NFA::constructKleeneClosure(RegExp regExp){
    assert(regExp.type == RegExpType::kleeneClosure);

    NFA finalNFA;

    NFA internalNFA = constructNFA(regExp.operands[0]);

    // connecting the start with start, and end with end
    finalNFA.startNode->addTransition(Pattern(), internalNFA.startNode);
    internalNFA.endNode->addTransition(Pattern(), finalNFA.endNode);

    // loop back
    internalNFA.endNode->addTransition(Pattern(), internalNFA.startNode);

    // skip transition
    finalNFA.startNode->addTransition(Pattern(), internalNFA.endNode);
    return finalNFA;
}

NFA NFA::constructPositiveClosure(RegExp regExp) {
    assert(regExp.type == RegExpType::positiveClosure);

    NFA finalNFA;

    NFA internalNFA = constructNFA(regExp.operands[0]);

    // connecting the start with start, and end with end
    finalNFA.startNode->addTransition(Pattern(), internalNFA.startNode);
    internalNFA.endNode->addTransition(Pattern(), finalNFA.endNode);

    // loop back
    internalNFA.endNode->addTransition(Pattern(), internalNFA.startNode);

    return finalNFA;
}

void printVector(std::vector<NFANode*> vec) {
    std::cout << "{";
    for (auto node: vec)
        std::cout << node << ",";
    std::cout << "}";
}

void NFA::print() {
    std::set<NFANode*> visited;
    std::queue<NFANode*> q;
    q.push(startNode);
    while(!q.empty()) {
        NFANode* node = q.front(); q.pop();

        if (visited.count(node) != 0)
            continue;
        visited.insert(node);

        for (auto transition: node->transitions) {
            for (NFANode* neighbour: transition.second){
                q.push(neighbour);
            }
        }
    }

//    std::cout << "\t\t";
//    for (char c: characters)
//        std::cout << c << "\t\t";
//    std::cout << "\n";

    for (auto node: visited) {
        std::cout << node;
        if (node->isFinal)
            std::cout << " (F): " << node->type;
        if (node == startNode)
            std::cout << " (S)";
        std::cout << "\t\t";

        for (auto transitions: node->transitions) {
            Pattern p = transitions.first;
            std::cout << p.print() << ":";
            printVector(transitions.second);
            std::cout << "\t";
        }
        std::cout << "\n";
    }

}



