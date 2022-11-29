//
// Created by youssef on 11/27/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
#ifndef COMPILERPROJECT_RULESPARSER_H
#define COMPILERPROJECT_RULESPARSER_H


class RulesParser {
    struct RegularLine {
        string LHS;
        string RHS;
    };
public:
    vector<string> keyWords;
    vector<char> punctuation;
    vector<RegularLine> regularDefinitions;
    vector<RegularLine> regularExpressions;
    int parseInputFile(string path);

private:
    int getLineType(string line);
    void parsePunctuationLine(string str);
    void parseKeywordLine(string str);
    void parseRegularLine(string str);
};


#endif //COMPILERPROJECT_RULESPARSER_H
