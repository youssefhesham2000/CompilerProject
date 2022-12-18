
#include "Production.h"
#include "../StringUtils.h"
Production Production::parseProduction(std::string str) {
    std::vector<std::vector<Symbol>> productions;
    str = StringUtils::removeLeadingAndTrailingSpaces(str);

    // first see if there is any disjunction.
    std::vector<std::string> disjunction =  getTopLevelDisjunction(str);

    for( auto it: disjunction) {
        //
        std::vector<std::string> concatenation =  getTopLevelConcatenation(it);
        std::vector<Symbol> temp;
        for (auto symbol: concatenation) {
            std::string  tempStr = getSymbol(symbol);
            if (tempStr != symbol){
                // if they don't match this means that the str had a leading and trailing
                // single quotes so it's a terminal symbol.
                temp.emplace_back(Symbol(tempStr, SymbolType::terminal));
            } else{
                temp.emplace_back(Symbol(symbol, SymbolType::nonTerminal));
            }
        }
        productions.emplace_back(temp);
    }
    return Production(productions);
}

Production::Production(std::vector<std::vector<Symbol>> productions) {
    this->productions = productions;
}

std::string Production::getSymbol(std::string str) {
    str = StringUtils::removeLeadingAndTrailingSpaces(str);
    return StringUtils::removeLeadingAndTrailingSingleQuotes(str);

}
std::vector<std::string> Production::getTopLevelDisjunction(std::string str) {
    return getTopLevelString('|', str);
}

std::vector<std::string> Production::getTopLevelConcatenation(std::string str) {
    return getTopLevelString(' ', str);
}

std::vector<std::string> Production::getTopLevelString(char delimiter, std::string str) {
    std::vector<std::string> productions;
    std::string temp = "";
    for(char it : str) {
        if( it == delimiter) {
            productions.push_back(temp);
            temp = "";
        } else{
            temp += it;
        }
    }
    if (temp != ""){
        productions.push_back(temp);
    }

    return productions;
}

