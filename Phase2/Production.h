

#ifndef COMPILERPROJECT_PRODUCTION_H
#define COMPILERPROJECT_PRODUCTION_H


#include <vector>
#include "Symbol.h"
#include "../Token.h"

enum class ProductionType { concatenation, disjunction, symbol, production };


class Production  {

    Symbol symbol;
    ProductionType type;
    std::vector<Production> productions;
private:
    Production(Symbol symbol,  ProductionType type);
    Production(std::vector<Production> productions, ProductionType type): productions(std::move(productions)), type(type) {}
    explicit Production(std::string production):production(production)  {
        type = ProductionType::production;
    };


public:
    std::string production;
    static Production parseProduction(std::string str);
    static std::string getSymbol(std::string str);
    static std::vector<std::string> getTopLevelDisjunction(std::string str);
    static std::vector<std::string> getTopLevelConcatenation(std::string str);
    static std::vector<std::string> getTopLevelString(char delimiter, std::string str);

};


#endif //COMPILERPROJECT_PRODUCTION_H
