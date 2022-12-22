

#ifndef COMPILERPROJECT_PRODUCTION_H
#define COMPILERPROJECT_PRODUCTION_H


#include <vector>
#include "Symbol.h"
#include "../Phase1/Token.h"



class Production  {
private:

public:
    // unordered_map needs the value type to have a default constructor
    Production()= default;
    explicit Production(std::vector<std::vector<Symbol>> productions);
    static std::vector<std::vector<Symbol>> parseProduction(std::string str);
    static std::string getSymbol(std::string str);
    static std::vector<std::string> getTopLevelDisjunction(std::string str);
    static std::vector<std::string> getTopLevelConcatenation(std::string str);
    static std::vector<std::string> getTopLevelString(char delimiter, std::string str);
    std::string toString();
    std::vector<std::vector<Symbol>> productions;

};


#endif //COMPILERPROJECT_PRODUCTION_H
