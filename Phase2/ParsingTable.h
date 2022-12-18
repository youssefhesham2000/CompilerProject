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
public:
    static ParsingTable generateParsingTable(std::unordered_map<std::string, std::string> CFGRules ,std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction> firstSet,
                                      std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction> followSet);

    // each production LHS maps to multiple Symbols that can have different
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>,HashFunction>,HashFunction> parsingTable;
private:
    ParsingTable(std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>,HashFunction>,HashFunction> parsingTable);

};


#endif //COMPILERPROJECT_PARSINGTABLE_H
