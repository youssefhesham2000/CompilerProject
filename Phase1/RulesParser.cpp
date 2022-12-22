//
// Created by youssef on 11/27/2022.
//

#include "RulesParser.h"
#include "../StringUtils.h"
#define REGULAR_DEFINITION_EQUAL '='
#define REGULAR_EXPRESSION_EQUAL ':'
#define PUNCUTUATION_OPEN_BRACKET '['
#define PUNCUTUATION_CLOSE_BRACKET ']'
#define KEYWORD_OPEN_BRACKET '{'
#define KEYWORD_CLOSE_BRACKET '}'
#define BACKSLASH '\\'
#define SPACE ' '
#define DEBUG true
using namespace std;

std::map<std::string, RegExp> RulesParser::regularDefinitionsMap;
int RulesParser::getLineType(string line) {
    if (line[0] == PUNCUTUATION_OPEN_BRACKET)
        return 0;
    else if (line[0] == KEYWORD_OPEN_BRACKET)
        return 1;
    return -1;
}

void RulesParser::parseKeywordLine(string str) {
    str.erase(remove(str.begin(), str.end(), KEYWORD_OPEN_BRACKET), str.end());
    str.erase(remove(str.begin(), str.end(), KEYWORD_CLOSE_BRACKET), str.end());

    istringstream ss(str);
    string word;
    while (ss >> word) {
        if (word == string(1, KEYWORD_OPEN_BRACKET) || word == string(1, KEYWORD_CLOSE_BRACKET))
            continue;
        keyWords.push_back(word);
    }
}

void RulesParser::parseRegularLine(string str) {
    string LHS = "";
    string RHS = "";
    bool isRegularExpression = false;
    int i = 0;

    while (str[i] != REGULAR_DEFINITION_EQUAL && str[i] != REGULAR_EXPRESSION_EQUAL) {
        LHS += str[i];
        i++;
    }
    if (str[i] == REGULAR_EXPRESSION_EQUAL) {
        isRegularExpression = true;
    }
    i++;
    while (i < str.length()) {
        RHS += str[i];
        i++;
    }
    RegularLine r;
    r.LHS = StringUtils::removeLeadingAndTrailingSpaces(LHS);
    r.RHS = RHS;
    if (isRegularExpression) {
        regularExpressions.push_back(r);
    } else {
        regularDefinitions.push_back(r);
    }
}
void RulesParser::parsePunctuationLine(string str) {
    for (int i = 1; i < str.length() - 1; i++) {
        if (str[i] == BACKSLASH || str[i] == SPACE)
            continue;
        punctuation.push_back(std::string(1, str[i]));
    }
}
// phase 2
void RulesParser::parseCFGRules(std::string path) {
    fstream reInputFile;
    reInputFile.open(path, ios::in);
    if (reInputFile.is_open()) {
        string temp;
        string LHS;
        string RHS;
        while (getline(reInputFile, temp)) {
            // If there is a new rule
            if(temp[0] == '#' ) {
                if(!LHS.empty() && !RHS.empty()) {
                    LHS = StringUtils::removeLeadingAndTrailingSpaces(LHS);
                    RHS = StringUtils::removeLeadingAndTrailingSpaces(RHS);
                    this->CFGRules.insert({LHS, RHS});
                    // clear the String to store new rule
                    LHS = "";
                    RHS = "";
                }
                int i = 1;
                // get LHS untill we reach the first =
                while (i< temp.length() && temp[i] != '=') {
                    LHS += temp[i];
                    i++;
                }
                i++;
                // get the rest of the line as RHS
                while (i < temp.length()) {
                    RHS+= temp[i];
                    i++;
                }
            } else{
                // if the line doesn't start with # so it's the rest of RHS for another rule
                int i = 0;
                while (i < temp.length()) {
                    RHS+= temp[i];
                    i++;
                }
            }
        }

        if(!LHS.empty() && !RHS.empty()) {
            LHS = StringUtils::removeLeadingAndTrailingSpaces(LHS);
            RHS = StringUtils::removeLeadingAndTrailingSpaces(RHS);
            this->CFGRules.insert({LHS, RHS});
            // clear the String to store new rule
            LHS = "";
            RHS = "";
        }
    } else {
        cout << "File Exception" << endl;
    }
    reInputFile.close();
}

int RulesParser::parseInputFile(string path) {
    fstream reInputFile;
    reInputFile.open(path, ios::in);
    if (reInputFile.is_open()) {
        string temp;
        while (getline(reInputFile, temp)) {
            int lineType = this->getLineType(temp);
            if (lineType == 0) {
                this->parsePunctuationLine(temp);
            } else if (lineType == 1) {
                this->parseKeywordLine(temp);
            } else {
                this->parseRegularLine(temp);
            }
        }
    } else {
        cout << "File Exception" << endl;
    }
    reInputFile.close();

//    for (RegularLine line: regularDefinitions) {
//        RegExp regExp = RegExp::parseRegExp(line.RHS);
//        regularDefinitionsMap[line.LHS] = regExp;
//    }
//
//    for (RegularLine line: regularExpressions) {
//        RegExp regExp = RegExp::parseRegExp(line.RHS);
//        regularDefinitionsMap[line.LHS] = regExp;
//    }

    if (!DEBUG)
        return 0;

    for (auto kv_pair: regularDefinitionsMap) {
        cout << kv_pair.first << " :" << endl;
        for (string line: kv_pair.second.toString())
            cout << line << endl;
        cout << "----------------------------------------\n";
    }

    /*
    cout << "regular expressions" << endl;
    for (auto &it : regularExpressions) {
        cout << it.LHS << '\n';
        cout << it.RHS << '\n';
    }
    cout << "regular defenitions" << endl;
    for (auto &it : regularDefinitions) {
        cout << it.LHS << '\n';
        cout << it.RHS << '\n';
    }

    cout << "KeyWords" << endl;
    for (auto &it : keyWords) {
        cout << it << '\n';
    }

    cout << "puncutuations" << endl;
    for (auto &it : punctuation) {
        cout << it << '\n';
    }
*/


    return 0;

}
