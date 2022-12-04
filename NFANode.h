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

    std::map<char, std::vector<NFANode>> transitions;
    int id;
    bool isFinal;
    std::string type; // int, id, num, ...
};


#endif //COMPILERPROJECT_NFANODE_H
