#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#ifndef COMPILERPROJECT_LEXICALRULESPARSER_H
#define COMPILERPROJECT_LEXICALRULESPARSER_H

#define REGULAR_DEFINITION_EQUAL '='
#define REGULAR_EXPRESSION_EQUAL ':'
#define PUNCUTUATION_OPEN_BRACKET '['
#define PUNCUTUATION_CLOSE_BRACKET ']'
#define KEYWORD_OPEN_BRACKET '{'
#define KEYWORD_CLOSE_BRACKET '}'
#define OR '|'
#define BACKSLASH '\\'
#define SPACE ' '
#define DEBUG true
using namespace std;
struct RegularLine {
    string LHS;
    string RHS;
};


/*
    returns 0 if the line is PUNCUTUATION
            1 if it is a Keywords
            else returns -1
*/
int getLineType(string line) {
    if (line[0] == PUNCUTUATION_OPEN_BRACKET)
        return 0;
    else if (line[0] == KEYWORD_OPEN_BRACKET)
        return 1;
    return -1;
}

//globals
vector<string> keyWords;
vector<char> puncutuation;
vector<RegularLine> regularDefinitions;
vector<RegularLine> regularExpressions;

void parsePuncutuationLine(string str) {
    for (int i = 1; i < str.length() - 1; i++) {
        if (str[i] == BACKSLASH || str[i] == SPACE)
            continue;
        puncutuation.push_back(str[i]);
    }
}

void parseKeywordLine(string str) {
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

void parseRegularLine(string str) {
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
    r.LHS = LHS;
    r.RHS = RHS;
    if (isRegularExpression) {
        regularExpressions.push_back(r);
    } else {
        regularDefinitions.push_back(r);
    }

}

int parseInputFile(string path) {
    fstream reInputFile;
    reInputFile.open(path, ios::in);
    if (reInputFile.is_open()) {
        string temp;
        while (getline(reInputFile, temp)) {
            int lineType = getLineType(temp);
            if (lineType == 0) {
                parsePuncutuationLine(temp);
            } else if (lineType == 1) {
                parseKeywordLine(temp);
            } else {
                parseRegularLine(temp);
            }
        }
    } else {
        cout << "File Exception" << endl;
    }
    reInputFile.close();
    if (DEBUG) {
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
        for (auto &it : puncutuation) {
            cout << it << '\n';
        }
    }

    return 0;

}

#endif // COMPILERPROJECT_LEXICALRULESPARSER_H
