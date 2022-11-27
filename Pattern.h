//
// Created by youssef on 11/27/2022.
//
#include <string>
#include "string.h"
#include "vector"
#include <array>

using namespace std;

#ifndef COMPILERPROJECT_PATTERN_H
#define COMPILERPROJECT_PATTERN_H

#define EPSILON "\\L"
#define OR '|'

class Pattern {

public:
    //for epsilon pattern.
    Pattern();
    Pattern(string pattern);
    //returns true if the pattern is epsilon.
    bool isPatternEpsilon();
    bool isPatternContains(char character);
    string getPattern();
private:
    bool isEpsilon;
    // indicates if the pattern is range or a specific char.
    bool isRange;
    string pattern;
    vector<array<char,2>> getRanges();

};


#endif //COMPILERPROJECT_PATTERN_H
