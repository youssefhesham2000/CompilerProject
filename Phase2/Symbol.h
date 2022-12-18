
#ifndef COMPILERPROJECT_SYMBOL_H
#define COMPILERPROJECT_SYMBOL_H


#include <string>
#include <cmath>

enum class SymbolType { terminal, nonTerminal};

class Symbol  {

public:
    SymbolType type;
    std::string symbol;
    bool operator==(const Symbol& s) const{
        return symbol == s.symbol;
    }

    size_t operator()(const Symbol& inKey) const;
     Symbol(std::string, SymbolType type);

};




#endif //COMPILERPROJECT_SYMBOL_H
