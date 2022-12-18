

#ifndef COMPILERPROJECT_PRODUCTION_H
#define COMPILERPROJECT_PRODUCTION_H


#include <vector>
#include "Symbol.h"
#include "../Phase1/Token.h"



class Production  {

    std::vector<std::vector<Symbol>> productions;
private:
    Production(std::vector<std::vector<Symbol>> productions);

public:
    static Production parseProduction(std::string str);
    static std::string getSymbol(std::string str);
    static std::vector<std::string> getTopLevelDisjunction(std::string str);
    static std::vector<std::string> getTopLevelConcatenation(std::string str);
    static std::vector<std::string> getTopLevelString(char delimiter, std::string str);

};


#endif //COMPILERPROJECT_PRODUCTION_H
