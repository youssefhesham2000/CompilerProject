

#include "ParsingTable.h"
#include "HashFunction.h"
#include "vector"
ParsingTable::ParsingTable(
        std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction>, HashFunction> parsingTable) {
    this->parsingTable = parsingTable;
}

