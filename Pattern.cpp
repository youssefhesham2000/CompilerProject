//
// Created by youssef on 11/27/2022.
//

#include "Pattern.h"

#define SPACE ' '
#define DASH '-'

Pattern::Pattern() {
    this->isEpsilon = true;
    this->pattern = EPSILON;
    this->isRange = false;
}

Pattern::Pattern(std::string pattern) {
    if (pattern.length() > 1){
        this->isRange=true;
    }
    else{
        this->isRange= false;
    }
    this->pattern = pattern;
    this->isEpsilon= false;
}

bool Pattern::isPatternEpsilon() {
    return this->isEpsilon;
}

string Pattern::getPattern() {
    return this->pattern;
}

vector<array<char,2>> Pattern::getRanges() {
    vector<array<char,2>> ranges;
    array<char,2> temp;
    int j = 0;
    for (int i = 0; i < pattern.length(); i++) {
        if (pattern[i] == SPACE || pattern[i] == DASH)
            continue;
        if (pattern[i] == OR) {
            ranges.push_back(temp);
            j = 0;
        }
        else {
            temp[j] =pattern[i];
            j++;
        }
    }
    return ranges;
}

bool Pattern::isPatternContains(char character) {
    if (!isRange){
        return character == pattern[0];
    }
    vector<array<char,2>> ranges = getRanges();
   for (auto &it : ranges) {
       if (character >= it[0] && character <= it[1])
           return true;
   }
    return false;
}


