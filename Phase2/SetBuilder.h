//
// Created by Abdallah on 12/22/2022.
//
#include <unordered_set>
#include <unordered_map>
#include "Symbol.h"
#include "Production.h"

#ifndef COMPILERPROJECT_SETBUILDER_H
#define COMPILERPROJECT_SETBUILDER_H



using SetMap = std::unordered_map<Symbol, std::unordered_set<Symbol>>;
using ProductionMap = std::unordered_map<Symbol, Production*>;
extern SetMap firstSet, followSet;

std::unordered_set<Symbol> getFirstSet(const Symbol& s, const ProductionMap& productions);
std::unordered_set<Symbol> getFirstSet(const std::vector<Symbol>& symbols, const ProductionMap& p);
void initFollowSet(const ProductionMap& productions);





#endif //COMPILERPROJECT_SETBUILDER_H
