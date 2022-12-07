//
// Created by Abdallah on 12/4/2022.
//
#include <vector>
#include <string>
#include <map>

#ifndef COMPILERPROJECT_NFANODE_H
#define COMPILERPROJECT_NFANODE_H

const char epsilonTransition = '\0';

class NFANode {

public:
    // Added in order to make set.insert work as it require operator in the user defined objects
    bool operator<(const NFANode& t) const
    {
        return (this->id < t.id);
    }
    std::map<char, std::vector<NFANode*>> transitions;
    int id;
    bool isFinal;
    std::string type; // int, id, num, ...
};


#endif //COMPILERPROJECT_NFANODE_H
