//
// Created by Abdallah on 12/22/2022.
//

#include <map>
#include "SetBuilder.h"

SetMap firstSet, followSet;

// Get the first of a string of symbols
std::unordered_set<Symbol> getFirstSet(const std::vector<Symbol>& symbols, const ProductionMap& productions) {
    if (symbols.empty())
        return {};

    static std::map<std::vector<Symbol>, std::unordered_set<Symbol>> cachedResults;
    if (cachedResults.find(symbols) != cachedResults.end())
        return cachedResults[symbols];

    std::unordered_set<Symbol> res;
    for (const Symbol& operand: symbols) {
        auto temp = getFirstSet(operand, productions);
        res.insert(temp.begin(), temp.end());

        if (temp.count(epsilonSymbol) == 0)
            break;
    }

    return cachedResults[symbols] = res;
}

std::unordered_set<Symbol> getFirstSet(const Symbol& s, const ProductionMap& productions) {
    if (firstSet.find(s) != firstSet.end())
        return firstSet[s];

    if (s.type == SymbolType::terminal)
        return firstSet[s] = {s};

    if (productions.find(s) == productions.end())
        throw std::runtime_error("Found a non-terminal " + s.symbol + " without productions");

    Production* p = productions.find(s)->second;
    std::unordered_set<Symbol> res;
    for (const std::vector<Symbol>& disjunctionOperand: p->productions) {
        auto temp = getFirstSet(disjunctionOperand, productions);
        res.insert(temp.begin(), temp.end());
    }
    return firstSet[s] = res;
}


std::unordered_set<Symbol> getFollowSet(const Symbol& s, const ProductionMap& productions) {
    if (followSet.find(s) != followSet.end())
        return followSet[s];


    std::unordered_set<Symbol> res;

    for (const auto& x: productions) {
        Symbol lhs = x.first;
        Production* p = x.second;

        for (auto disjunctionOperands: p->productions) {
            auto it = disjunctionOperands.begin();
            for (;(it+1) != disjunctionOperands.end();it++) {
                auto operand = *it;
                if (operand == s) {
                    // Get the first set of the rest of the operands
                    auto temp = getFirstSet(std::vector<Symbol>(it + 1, disjunctionOperands.end()), productions);

                    // Special case if the rest of operands derive epsilon
                    if (temp.count(epsilonSymbol) != 0) {
                        auto lhsFollowSet = getFollowSet(lhs, productions);
                        res.insert(lhsFollowSet.begin(), lhsFollowSet.end());
                        temp.erase(epsilonSymbol);
                    }
                    res.insert(temp.begin(), temp.end());
                }
            }

            // Check if final element == s
            if (*it == s){
                auto lhsFollowSet = getFollowSet(lhs, productions);
                res.insert(lhsFollowSet.begin(), lhsFollowSet.end());
            }
        }
    }


    return followSet[s] = res;
}
