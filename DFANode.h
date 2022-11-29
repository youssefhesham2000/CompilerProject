#ifndef COMPILERPROJECT_DFANODE_H
#define COMPILERPROJECT_DFANODE_H

#include <map>
#include <string>

class DFANode{
private:
public:
    std::map<char, DFANode> transitions;
    int id;
    bool isFinal;
    std::string type;
};

#endif //COMPILERPROJECT_DFANODE_H
