//
// Created by Abdallah on 12/23/2022.
//

#include <stack>
#include <iostream>
#include "Parser.h"

void Parser::match(const ParsingTable &p, std::vector<Symbol> &input, const Symbol &start,
                   const std::unordered_map<Symbol, std::unordered_set<Symbol>> &followSet){
    auto parsingTable = p.parsingTable;
    std::stack<Symbol> stck;
    stck.push(endOfParsingSymbol);
    stck.push(start);


    auto currentInput = input.begin();

    while (stck.top() != endOfParsingSymbol) {
        Symbol top = stck.top();

        if (*currentInput == top) {
            stck.pop();
            std::cout << "Matched: " << currentInput->symbol << std::endl;
            currentInput++;
        } else if (top.type == SymbolType::terminal) {
            std::cout << "Error: expected '" + top.symbol << "', but found '" << currentInput->symbol << "', inserting it and continuing" << std::endl;
            int idx = currentInput - input.begin();
            input.insert(currentInput, top);
            currentInput = input.begin() + idx + 1;
            stck.pop();
        } else if (parsingTable[top][*currentInput].empty()) {
            std::cout << "Error: Found empty cell in transition table for " << top.symbol << " -> " << currentInput->symbol
                      << std::endl;
            std::cout << "Skipping tokens until a non-terminal in FOLLOW(" << top.symbol << ")" << std::endl;
            while (followSet.at(top).count(*currentInput) == 0){
                currentInput++;

                if (currentInput == input.end()){
                    std::cout << "Failed to recover\n";
                    return;
                }
            }
            stck.pop();
        } else {
            stck.pop();
            std::vector<Symbol> production = parsingTable[top][*currentInput];
            std::cout << "Using production: " << top.symbol << " -> ";
            for (auto s: production)std::cout << (s == epsilonSymbol ? "e" : s.symbol)  << ",";
            std::cout << std::endl;

            if (production[0] != epsilonSymbol)
                for (int i = production.size()-1;i >= 0;i--)
                    stck.push(production[i]);
        }

        // Print everything matched so far
        for (auto it = input.begin(); it != currentInput;it++) std::cout << it->symbol << " ";
        std::cout << "|| ";
        // Print stack
        auto stckCopy = stck;
        while (stckCopy.size() > 1) {
            std::cout << stckCopy.top().symbol << " ";
            stckCopy.pop();
        }
        std::cout << std::endl << std::endl;
    }
}
