

#include "ParsingTable.h"

#include <utility>
#include <iostream>
#include "vector"
#include "Production.h"
#include "SetBuilder.h"

ParsingTable::ParsingTable(
        std::unordered_map<Symbol, std::unordered_map<Symbol, std::vector<Symbol>>> parsingTable) {
    this->parsingTable = std::move(parsingTable);
}

ParsingTable ParsingTable::generateParsingTable(const std::unordered_map<Symbol, Production*>& rules,
                                                const std::unordered_map<Symbol, std::unordered_set<Symbol>>& firstSet,
                                                const std::unordered_map<Symbol, std::unordered_set<Symbol>>& followSet) {


    std::unordered_map<Symbol, std::unordered_map<Symbol, std::vector<Symbol>>> parsingTable;
    for(const auto& rule: rules) {
        Symbol s = rule.first;

        for (const std::vector<Symbol> p: rule.second->productions) {
            const auto first = getFirstSet(p, rules);
            // Default case
            for (const Symbol &terminal: first) {
                if (terminal == epsilonSymbol)
                    continue;

                if (parsingTable[s].find(terminal) != parsingTable[s].end())
                    throw std::runtime_error("Ambiguous grammar (1)");

                parsingTable[s][terminal] = p;
            }

            if (first.count(epsilonSymbol) != 0) {
                auto follow = followSet.find(s)->second;
                for (const Symbol &terminal: follow) {
                    if (terminal == epsilonSymbol)
                        continue;

                    if (parsingTable[s].find(terminal) != parsingTable[s].end())
                        throw std::runtime_error("Ambiguous grammar (2)");

                    parsingTable[s][terminal] = p;
                }
            }
        }
    }
//        // The non terminal symbol row entry in the table :M[A,...].
//        std::unordered_map<Symbol, std::unordered_set<Symbol>> symbolRowEntry;
//
//        if(firstSet.find(symbol) == firstSet.end()|| followSet.find(symbol)== followSet.end()){
//            throw "Illeagal arguments";
//        }
//        std::unordered_set<Symbol> SymbolFirstSet = firstSet.find(symbol)->second;
//        std::unordered_set<Symbol> SymbolFollowSet = followSet.find(symbol)->second;
//
//        for (Symbol terminalSymbol: SymbolFirstSet) {
//            // the terminal col entry in the row entry :M[A,a].
//            std::unordered_set<Symbol> terminalSymbolColEntry;
//            // The col entry is not empty and there are symbols in it.
//            if(symbolRowEntry.find(terminalSymbol) != symbolRowEntry.end()) {
//                terminalSymbolColEntry = symbolRowEntry.find(terminalSymbol)->second;
//            }
//
//            if(terminalSymbol ==  epsilonSymbol) {
//                for(Symbol followingTerminalSymbol: SymbolFollowSet) {
//                    if(symbolRowEntry.find(followingTerminalSymbol) != symbolRowEntry.end()){
//                        // Add alpha to M[A,b] if the entry exist.
//                        symbolRowEntry.find(followingTerminalSymbol)->second.insert(terminalSymbol);
//                    } else{
//                        // The col entry doesn't exist.
//                        std::unordered_set<Symbol> tempColEntry;
//                        tempColEntry.insert(terminalSymbol);
//                        symbolRowEntry.insert({followingTerminalSymbol, tempColEntry});
//                    }
//                }
//            } else if(terminalSymbol != endOfParsingSymbol){
//                terminalSymbolColEntry.insert(terminalSymbol);
//            }
//            symbolRowEntry.insert({terminalSymbol, terminalSymbolColEntry});
//        }
//        parsingTable.insert({symbol, symbolRowEntry});
//    }
    return ParsingTable(parsingTable);
}

std::string vectorHelper(std::vector<Symbol> v){
    std::string ans = "[";
    for (auto& s: v)
        ans += s.symbol + ", ";
    ans += "]";
    return ans;
}

void ParsingTable::print() {
    std::cout << "\n\nParsing table:\n";
    for (const auto& row: parsingTable) {
        const auto& lhsSymbol = row.first;
        std::cout << lhsSymbol.symbol << " = ";

        for (const auto& col: row.second){
            const auto& terminal = col.first;
            const auto& production = col.second;
            std::cout << terminal.symbol << ":" << vectorHelper(production) << " || ";
        }

        std::cout << std::endl;
    }
}