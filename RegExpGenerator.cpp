//
// Created by mohamed on 12/5/2022.
//

#include "RegExpGenerator.h"
/**
 * intiates the Generator by creating all teh regular definitions that might be used.
 * @param regularDefintionVector
 */
RegExpGenerator::RegExpGenerator(std::vector<RulesParser::RegularLine> regularDefintionVector) {
    queue<std::string> LHS;
    for(auto item: regularDefintionVector) {
        regularDefinitions.insert({item.LHS, item.RHS});
        LHS.push(item.LHS);
    }
    while (!LHS.empty()) {
        std::string currentLHS = LHS.front();
        LHS.pop();
        std::string currentRHS = regularDefinitions.find(currentLHS)->second;
        for (auto it: regularDefinitions) {
            //check if the current RHS contains a REgDefinition inside it's RHS and this REgDefinition not evaluated yet.
            if (currentRHS.find(it.first)!= string::npos && !regularDefinitionsToRegExp.count(it.first)) {
                LHS.push(currentLHS);
            } else{
               // either the RHS doesn't contain any other definitions or they are already evaluated.
                RegExp currentRegExp = RegExp::parseRegExp(currentRHS, regularDefinitionsToRegExp);
               //add evaluated RegExp to the map
                regularDefinitionsToRegExp.insert({currentLHS, currentRegExp});
            }
        }
    }
}
/**
 *
 * @param parser RulesParser contains the parsing output of the file.
 * @return  map of string types into RegExp
 */
map<std::string,RegExp>RegExpGenerator::generateAllExpressions(RulesParser parser) {
    map<std::string, RegExp> parsedRegExp;

    //Add regular definitions to the map.
    for(auto item: regularDefinitionsToRegExp) {
        parsedRegExp.insert({item.first, item.second});
    }
    // parse regular expression first.
    for (auto item: parser.regularExpressions) {
        RegExp currentRegExp = RegExp::parseRegExp(item.RHS, this->regularDefinitionsToRegExp);
        parsedRegExp.insert({item.LHS, currentRegExp});
    }

    // parse KeyWords.
    for(auto item: parser.keyWords) {
        RegExp currentRegExp = RegExp::parseKeyWord(item, this->regularDefinitionsToRegExp);
        parsedRegExp.insert({item, currentRegExp});
    }

    // parse punctuation.
    for(auto item: parser.punctuation) {
        RegExp currentRegExp = RegExp::parsePunctuations(item, this->regularDefinitionsToRegExp);
        parsedRegExp.insert({item, currentRegExp});
    }
    return parsedRegExp;
}