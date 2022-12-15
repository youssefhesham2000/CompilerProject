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
    explicit Pattern(char c);
    explicit Pattern(char start, char end);
    bool isEpsilon() const;
    bool match(char character);
    bool operator== (const Pattern) const;
    bool operator< (const Pattern) const;
    string print();
    std::vector<char> getMatches();

private:
    bool epsilon;
    bool range;
    string pattern;
    pair<char, char> getRange() const;


};


#endif //COMPILERPROJECT_PATTERN_H
