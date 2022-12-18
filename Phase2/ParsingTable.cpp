//
// Created by mohamed on 12/18/2022.
//

#include "ParsingTable.h"
#include "HashFunction.h"

ParsingTable::ParsingTable(
        std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction>, HashFunction> parsingTable) {
    this->parsingTable = parsingTable;
}