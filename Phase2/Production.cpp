
#include "Production.h"
#include "../StringUtils.h"
Production Production::parseProduction(std::string str) {
    std::vector<Production> productions;
    ProductionType type;
    str = StringUtils::removeLeadingAndTrailingSpaces(str);
    // first see if there is any disjunction as it has priority over concatenation.
    std::vector<std::string> disjunction =  getTopLevelDisjunction(str);
    if (disjunction.size()>1) {
        type = ProductionType::disjunction;
        for (const auto& production: disjunction) {
            productions.push_back(parseProduction(production));
        }
        return Production(productions, type);
    }

    // then check for concatenation.
    std::vector<std::string> concatenation =  getTopLevelConcatenation(str);
    if (concatenation.size()>1) {
        type = ProductionType::concatenation;
        for (const auto& production: concatenation) {
            productions.push_back(parseProduction(production));
        }
        return Production(productions, type);
    }

    // check if it is a  symbol.
    std::string  tempStr = getSymbol(str);
    if (tempStr != str){
        // if they don't match this means that the str had a leading and trailing single quotes so it's a symbol.
        return Production(Symbol(tempStr), ProductionType::symbol );
    }

    // else it's a nested Production.
    return Production(str);


}
Production::Production(Symbol symbol, ProductionType type) {
    this->symbol = symbol;
    this->type = type;
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

