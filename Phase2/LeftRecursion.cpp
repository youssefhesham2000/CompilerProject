//
// Created by mohamed on 12/25/2022.
//

#include <iostream>
#include "LeftRecursion.h"
#include "map"
std::unordered_map<Symbol, Production *>
LeftRecursion::eliminateLeftRecursion(std::unordered_map<std::string , Production *> currentRules, std::vector<std::string> LHS) {

    for (int i = 0; i < LHS.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            std::vector<std::vector<Symbol>> tempProduction = currentRules[LHS[i]]->productions;
            std::vector<std::vector<Symbol>> outputProduction;
            std::vector<Production *> toBeReplaced;
            std::vector<std::string> lhsToBeReplaced;
            for (auto row:tempProduction) {
                for (auto cell:row) {
                    if (cell.symbol == LHS[j]){
                        toBeReplaced.emplace_back(currentRules[LHS[j]]);
                        lhsToBeReplaced.emplace_back(LHS[j]);
                    }
                }
            }
            if(toBeReplaced.size()!=0) {
                // substitute all the occurences.
                currentRules[LHS[i]]->productions = substituteSymbols(toBeReplaced, LHS, tempProduction);
            }
        }
        std::unordered_map<std::string , Production *> newRules = eliminateImmediateLeftRecursion(currentRules[LHS[i]]->productions, LHS[i]);
        std::cout<<newRules.size()<<std::endl ;

    }

    // convert it to the input format that suits the first and follow set.
    std::unordered_map<Symbol, Production *> output;
    for (int i = 0; i < LHS.size(); ++i) {
        output.insert({Symbol(LHS[i], SymbolType::nonTerminal), currentRules[LHS[i]]});
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

std::unordered_map<std::string , Production *> LeftRecursion::eliminateImmediateLeftRecursion(std::vector<std::vector<Symbol>> productions,
                                                                                                     std::string LHS) {
    std::vector<std::vector<Symbol>> betas;
    std::vector<std::vector<Symbol>> alphas;
    for (int i = 0; i < productions.size(); ++i) {
        if (productions[i][0].symbol == LHS ){
            // Immediate left recursion exist update alphas
            std::vector<Symbol> currentAlpha;
            for (int j = 1; j < productions[i].size(); ++j) {
                currentAlpha.emplace_back(productions[i][j]);
            }
            alphas.emplace_back(currentAlpha);
        }
        else {
            // No immediate left recursion so put in Betas.
            betas.emplace_back(productions[i]);
        }
    }
    std::unordered_map<std::string , Production *> returnedRules;
    if (alphas.size() != 0) {
        // there are immediate left recursion.
        // construct rule for betas.
        std::vector<std::vector<Symbol>> currentRuleProduction;
        Symbol newLHS = Symbol(LHS + "`", SymbolType::nonTerminal);
        Symbol epsilon = Symbol(LHS + "\\L", SymbolType::terminal);
        for (int i = 0; i < betas.size(); ++i) {
            currentRuleProduction.emplace_back(betas[i]);
            currentRuleProduction[i].emplace_back(newLHS);
        }
        returnedRules.insert({LHS,new Production(currentRuleProduction)});

        // construct rule for alphas.
        currentRuleProduction.clear();
        for (int i = 0; i < alphas.size(); ++i) {
            currentRuleProduction.emplace_back(alphas[i]);
            currentRuleProduction[i].emplace_back(newLHS);
        }
        // add epsilon to the end
        std::vector<Symbol> temp;
        temp.emplace_back(epsilon);
        currentRuleProduction.emplace_back(temp);

        returnedRules.insert({LHS + "`",new Production(currentRuleProduction)});

    } else{
        returnedRules.insert({LHS ,new Production(productions)});
    }
    return returnedRules;
}