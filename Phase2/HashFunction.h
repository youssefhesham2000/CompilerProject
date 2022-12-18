//
// Created by mohamed on 12/18/2022.
//

#ifndef COMPILERPROJECT_HASHFUNCTION_H
#define COMPILERPROJECT_HASHFUNCTION_H

#include <typeindex>
#include <string>
#include "Symbol.h"

class HashFunction {
public:
    std::hash<std::string> hasher;
    //using sum of length as hash function
    size_t operator()(const Symbol& s) const{
        return hasher(s.symbol);
    }
};
#endif //COMPILERPROJECT_HASHFUNCTION_H
