//
// Created by mohamed on 12/18/2022.
//

#include "unordered_map"
#include "unordered_set"
#include "Symbol.h"
#include "HashFunction.h"
#ifndef COMPILERPROJECT_PARSINGTABLE_H
#define COMPILERPROJECT_PARSINGTABLE_H


class ParsingTable {
    // each production LHS maps to multiple Symbols that can have different
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>,HashFunction>,HashFunction> parsingTable;
    ParsingTable(std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>,HashFunction>,HashFunction> parsingTable);

};


#endif //COMPILERPROJECT_PARSINGTABLE_H
