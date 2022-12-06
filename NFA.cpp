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
            return constructDisjunction(regExp);
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
    for(auto& nfa: NFAs) {
        combinedNFA.startNode->transitions[epsilonTransition].push_back(nfa.startNode);
    }
    return combinedNFA;
}


NFA::NFA(char c){
    startNode->transitions[c].push_back(endNode);
}

// THOMPSON CONSTRUCTION HELPERS
// All these constructors don't set any isFinal on any nodes, just creates the connections
NFA NFA::constructConcatenation(RegExp regExp){
    assert(regExp.type == RegExpType::concatenation);

    // first operand
    NFA combinedNFA = constructNFA(regExp.operands[0]);

    // remaining operands
    for (int i = 1;i < regExp.operands.size();i++) {
        NFA nfa = constructNFA(regExp.operands[i]);
        combinedNFA.endNode->transitions[epsilonTransition].push_back(nfa.startNode);
    }
    return combinedNFA;
}

NFA NFA::constructDisjunction(RegExp regExp){
    assert(regExp.type == RegExpType::disjunction || regExp.type == RegExpType::range);

    NFA combinedNFA;

    for (RegExp operand: regExp.operands) {
        NFA nfa = constructNFA(operand);

        combinedNFA.startNode->transitions[epsilonTransition].push_back(nfa.startNode);

        nfa.endNode->transitions[epsilonTransition].push_back(combinedNFA.endNode);
    }

    return combinedNFA;
}

NFA NFA::constructKleeneClosure(RegExp regExp){
    assert(regExp.type == RegExpType::kleeneClosure);

    NFA finalNFA;

    NFA internalNFA = constructNFA(regExp.operands[0]);

    // connecting the start with start, and end with end
    finalNFA.startNode->transitions[epsilonTransition].push_back(internalNFA.startNode);
    internalNFA.endNode->transitions[epsilonTransition].push_back(finalNFA.endNode);

    // loop back
    internalNFA.endNode->transitions[epsilonTransition].push_back(internalNFA.startNode);

    // skip transition
    finalNFA.startNode->transitions[epsilonTransition].push_back(internalNFA.endNode);
    return finalNFA;
}

NFA NFA::constructPositiveClosure(RegExp regExp) {
    assert(regExp.type == RegExpType::positiveClosure);

    NFA finalNFA;

    NFA internalNFA = constructNFA(regExp.operands[0]);

    // connecting the start with start, and end with end
    finalNFA.startNode->transitions[epsilonTransition].push_back(internalNFA.startNode);
    internalNFA.endNode->transitions[epsilonTransition].push_back(finalNFA.endNode);

    // loop back
    internalNFA.endNode->transitions[epsilonTransition].push_back(internalNFA.startNode);

    return finalNFA;
}

void printVector(std::vector<NFANode*> vec) {
    std::cout << "{";
    for (auto node: vec)
        std::cout << node << ",";
    std::cout << "}";
}

void NFA::print() {
    std::map<NFANode*, std::map<char, std::vector<NFANode*>>> table;

    std::set<char> characters;
    std::set<NFANode*> visited;
    std::queue<NFANode*> q;

    q.push(startNode);
    while(!q.empty()) {
        NFANode* node = q.front(); q.pop();

        if (visited.count(node) != 0)
            continue;
        visited.insert(node);

        for (auto transition: node->transitions) {
            char c = transition.first;
            characters.insert(c);
            for (NFANode* neighbour: transition.second){
                table[node][c].push_back(neighbour);
                q.push(neighbour);
            }
        }
    }

//    std::cout << "\t\t";
//    for (char c: characters)
//        std::cout << c << "\t\t";
//    std::cout << "\n";

    for (auto row: table) {
        std::cout << row.first;
        if (row.first->isFinal)
            std::cout << " (F): " << row.first->type;
        if (row.first == startNode)
            std::cout << " (S)";
        std::cout << "\t\t";
        for (char c: characters) {
            std::cout << c << ":";
            printVector(table[row.first][c]);
            std::cout << "\t";
        }
        std::cout << "\n";
    }

}



