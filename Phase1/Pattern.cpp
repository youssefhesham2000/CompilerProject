//
// Created by youssef on 11/27/2022.
//

#include "Pattern.h"
#include "../StringUtils.h"
#include "NFANode.h"

Pattern::Pattern() {
    this->epsilon = true;
    this->pattern = epsilonTransition;
    this->range = false;
}

Pattern::Pattern(char c) {
    this->pattern = c;
    this->range = false;
    this->epsilon= false;
}

Pattern::Pattern(char start, char end) {
    this->pattern = std::string(1, start) + "-" + std::string(1, end);
    this->range = true;
    this->epsilon= false;
}

bool Pattern::isEpsilon() const{
    return this->epsilon;
}


pair<char, char> Pattern::getRange() const{
    return make_pair(pattern[0], pattern[2]);
}

bool Pattern::match(char character) {
    if (!range){
        return character == pattern[0];
    }

    pair<char, char> range = getRange();
    return character >= range.first && character <= range.second;
}


bool Pattern::operator==(const Pattern p) const{
    if (p.isEpsilon() && this->isEpsilon())
        return true;
    if (p.range && this->range && p.getRange() == this->getRange())
        return true;
    if (p.pattern.size() == 1 && this->pattern.size() == 1 && p.pattern[0] == this->pattern[0])
        return true;

    return false;
}


std::vector<char> Pattern::getMatches(){
    if (epsilon)
        return {epsilonTransition};

    if (!range)
        return {pattern[0]};

    std::vector<char> matches;
    for (char c = pattern[0]; c <= pattern[2];c++){
        matches.push_back(c);
    }
    return matches;

}

string Pattern::print(){
    if (!epsilon)
        return pattern;
    return "eps";
}
