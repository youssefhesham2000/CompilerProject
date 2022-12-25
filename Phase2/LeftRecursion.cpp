//
// Created by mohamed on 12/25/2022.
//

#include <iostream>
#include "LeftRecursion.h"
#include "map"
std::unordered_map<Symbol, Production *>
LeftRecursion::eliminateLeftRecursion(std::unordered_map<std::string , Production *> rules, std::vector<std::string> LHS) {

    for (int i = 0; i < LHS.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            std::vector<std::vector<Symbol>> tempProduction = rules[LHS[i]]->productions;
            std::vector<std::vector<Symbol>> outputProduction;
            std::vector<Production *> toBeReplaced;
            std::vector<std::string> lhsToBeReplaced;
            for (auto row:tempProduction) {
                for (auto cell:row) {
                    if (cell.symbol == LHS[j]){
                        toBeReplaced.emplace_back(rules[LHS[j]]);
                        lhsToBeReplaced.emplace_back(LHS[j]);
                    }
                }
            }
            if(toBeReplaced.size()!=0) {
                // substitute all the occurences.
                rules[LHS[i]]->productions = substituteSymbols(toBeReplaced, LHS, tempProduction);
            }
        }
    }

    // convert it to the input format that suits the first and follow set.
    std::unordered_map<Symbol, Production *> output;
    for (int i = 0; i < LHS.size(); ++i) {
        output.insert({Symbol(LHS[i], SymbolType::nonTerminal),rules[LHS[i]]});
    }
    return output;
}

std::vector<std::vector<Symbol>>
LeftRecursion::substituteSymbols(std::vector<Production *>productionToBeReplaced, std::vector<std::string> productionLHS,
                                std::vector<std::vector<Symbol>> performedOn) {
    std::vector<std::vector<Symbol>> output;
    for (int i = 0; i < productionToBeReplaced.size(); ++i) {
        Production* currentProduction =  productionToBeReplaced[i];
        for (int j = 0; j < performedOn.size(); ++j) {
            int k = 0;
            std::vector<std::vector<Symbol>> currentRow;
            for (int l = 0; l < currentProduction->productions.size(); ++l) {
                std::vector<Symbol> temp;
                currentRow.emplace_back(temp);
            }
            while (k<performedOn[j].size() && performedOn[j][k].symbol != productionLHS[i]){
                for (int l = 0; l < currentProduction->productions.size(); ++l) {
                    currentRow[l].emplace_back(performedOn[j][k]);
                }
                k++;
            }
            if (k == performedOn[j].size()){
                // the production not found.
                output.emplace_back(performedOn[j]);
            } else{
                // production is found
                for (int l = 0; l < currentProduction->productions.size(); ++l) {
                    // replace the production
                    currentRow[l].insert(currentRow[l].end(),currentProduction->productions[l].begin(),currentProduction->productions[l].end());
                }
                k++;
                while (k<performedOn[j].size() && performedOn[j][k].symbol != productionLHS[i]){
                    for (int l = 0; l < currentProduction->productions.size(); ++l) {
                        currentRow[l].emplace_back(performedOn[j][k]);
                    }
                    k++;
                }
                for (int l = 0; l < currentProduction->productions.size(); ++l) {
                    output.emplace_back(currentRow[l]);
                }
            }
        }
        performedOn = output;
    }
    return performedOn;
}