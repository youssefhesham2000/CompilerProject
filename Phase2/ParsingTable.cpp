

#include "ParsingTable.h"
#include "HashFunction.h"
#include "vector"

const std::string ParsingTable::epsilonSymbol = "\0";
const std::string ParsingTable::endOfParsingSymbol = "$";

ParsingTable::ParsingTable(
        std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction>, HashFunction> parsingTable) {
    this->parsingTable = parsingTable;
}

ParsingTable ParsingTable::generateParsingTable(std::unordered_map<std::string, std::string> CFGRules,
                                                std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction> firstSet,
                                                std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>, HashFunction> followSet) {

    // Create LHS Symbols.
    std::vector<Symbol> LHS;
    for(auto it: CFGRules) {
        LHS.emplace_back(Symbol(it.first, SymbolType::nonTerminal));
    }
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>,HashFunction>,HashFunction> parsingTable;
    for( Symbol symbol: LHS) {
        // The non terminal symbol row entry in the table :M[A,...].
        std::unordered_map<Symbol, std::unordered_set<Symbol, HashFunction>,HashFunction> symbolRowEntry;

        if(firstSet.find(symbol) == firstSet.end()|| followSet.find(symbol)== followSet.end()){
            throw "Illeagal arguments";
        }
        std::unordered_set<Symbol, HashFunction> SymbolFirstSet = firstSet.find(symbol)->second;
        std::unordered_set<Symbol, HashFunction> SymbolFollowSet = followSet.find(symbol)->second;

        for (Symbol terminalSymbol: SymbolFirstSet) {
            // the terminal col entry in the row entry :M[A,a].
            std::unordered_set<Symbol, HashFunction> terminalSymbolColEntry;
            // The col entry is not empty and there are symbols in it.
            if(symbolRowEntry.find(terminalSymbol) != symbolRowEntry.end()) {
                terminalSymbolColEntry = symbolRowEntry.find(terminalSymbol)->second;
            }

            if(terminalSymbol.symbol ==  epsilonSymbol) {
                for(Symbol followingTerminalSymbol: SymbolFollowSet) {
                    if(symbolRowEntry.find(followingTerminalSymbol) != symbolRowEntry.end()){
                        // Add alpha to M[A,b] if the entry exist.
                        symbolRowEntry.find(followingTerminalSymbol)->second.insert(terminalSymbol);
                    } else{
                        // The col entry doesn't exist.
                        std::unordered_set<Symbol, HashFunction> tempColEntry;
                        tempColEntry.insert(terminalSymbol);
                        symbolRowEntry.insert({followingTerminalSymbol, tempColEntry});
                    }
                }
            } else if(terminalSymbol.symbol != endOfParsingSymbol){
                terminalSymbolColEntry.insert(terminalSymbol);
            }
            symbolRowEntry.insert({terminalSymbol, terminalSymbolColEntry});
        }
        parsingTable.insert({symbol, symbolRowEntry});
    }
    return ParsingTable(parsingTable);
}