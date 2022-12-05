//
// Created by mohamed on 12/5/2022.
//
#include "string"
#include "map"
#include "RulesParser.h"
#include "vector"

#ifndef COMPILERPROJECT_REGEXPGENERATOR_H
#define COMPILERPROJECT_REGEXPGENERATOR_H


class RegExpGenerator {
private:
    std::map<std::string, std::string> regularDefinitions;
     // Maps the left hand side to the associated REGExp.
    std::map<std::string, RegExp> regularDefinitionsToRegExp;
public:
    RegExpGenerator(std::vector<RulesParser::RegularLine> regularDefinitionVector);

    //maps each type to the associated  RegExp
    map<std::string, RegExp> generateAllExpressions(RulesParser parser);



};


#endif //COMPILERPROJECT_REGEXPGENERATOR_H
