//
// Created by youssef on 11/27/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "RegExp.h"
using namespace std;
#ifndef COMPILERPROJECT_RULESPARSER_H
#define COMPILERPROJECT_RULESPARSER_H


class RulesParser {
public:
    struct RegularLine {
        string LHS;
        string RHS;
    };
    vector<string> keyWords;
    vector<string> punctuation;
    vector<RegularLine> regularDefinitions;
    vector<RegularLine> regularExpressions;
    static std::map<std::string, RegExp> regularDefinitionsMap;
    int parseInputFile(string path);


private:
    int getLineType(string line);
    void parsePunctuationLine(string str);
    void parseKeywordLine(string str);
    void parseRegularLine(string str);
};


#endif //COMPILERPROJECT_RULESPARSER_H
