#include <set>
#include <iostream>
#include "TransitionTable.h"

void TransitionTable::addState(DFANode* node) {
    for(const auto& p: node->transitions) {
        char transitionChar = p.first;
        int successorId = p.second->id;
        this->table[node->id][transitionChar] = successorId;
    }
}

void TransitionTable::print() {
    //  for reference  std::map<int, std::map<char, int>> table;


    // get all chars
    std::set<char> characterSet;
    for (auto row: table) {
        for (auto column: row.second){
            characterSet.insert(column.first);
        }
    }

    for (char c: characterSet)
        std::cout << "\t" << c;
    std::cout << std::endl;


    for (auto row: table) {
        std::cout << row.first << "\t";
        for (char c: characterSet){
            if (row.second.find(c) != row.second.end())
                std::cout << row.second[c];
            std::cout << "\t";
        }
        std::cout << std::endl;
    }

}
