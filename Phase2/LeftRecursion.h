//
// Created by mohamed on 12/25/2022.
//
#include "vector"
#include "Symbol.h"
#include "Production.h"
#include "unordered_map"
#ifndef COMPILERPROJECT_LEFTRECURSION_H
#define COMPILERPROJECT_LEFTRECURSION_H


class LeftRecursion {
    std::unordered_map<std::string , Production *> eliminateImmediateLeftRecursion(std::vector<std::vector<Symbol>> productions,
                                                                                                  std::string LHS);
    std::vector<std::vector<Symbol>> substituteSymbols(std::vector<Production*> productionsToBeReplaced, std::vector<std::string> productionLHS,std::vector<std::vector<Symbol>> performedOn );

public:
    std::unordered_map<Symbol, Production *> eliminateLeftRecursion(std::unordered_map<std::string , Production *> currentRules, std::vector<std::string> LHS);
};


#endif //COMPILERPROJECT_LEFTRECURSION_H
