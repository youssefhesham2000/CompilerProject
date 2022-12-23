//
// Created by Abdallah on 12/23/2022.
//

#ifndef COMPILERPROJECT_PARSER_H
#define COMPILERPROJECT_PARSER_H


#include "ParsingTable.h"

class Parser {
public:

    static void match(const ParsingTable &p, const std::vector<Symbol> &input, const Symbol &start,
                      const std::unordered_map<Symbol, std::unordered_set<Symbol>> &followSet);

};


#endif //COMPILERPROJECT_PARSER_H
