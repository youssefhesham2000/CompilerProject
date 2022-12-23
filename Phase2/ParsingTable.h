//
// Created by mohamed on 12/18/2022.
//

#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "Symbol.h"
#include "Production.h"

#ifndef COMPILERPROJECT_PARSINGTABLE_H
#define COMPILERPROJECT_PARSINGTABLE_H


class ParsingTable {
public:

    static ParsingTable generateParsingTable(const std::unordered_map<Symbol, Production*>& rules,
                                             const std::unordered_map<Symbol, std::unordered_set<Symbol>>& firstSet,
                                             const std::unordered_map<Symbol, std::unordered_set<Symbol>>& followSet);

    // each production LHS maps to multiple Symbols that can have different
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::vector<Symbol>>> parsingTable;
    void print();
private:
    ParsingTable(std::unordered_map<Symbol, std::unordered_map<Symbol, std::vector<Symbol>>> parsingTable);
};


#endif //COMPILERPROJECT_PARSINGTABLE_H
