
#ifndef COMPILERPROJECT_SYMBOL_H
#define COMPILERPROJECT_SYMBOL_H


#include <string>
enum class SymbolType { terminal, nonTerminal};
class Symbol  {
    SymbolType type;
    std::string symbol;
public:
     Symbol(std::string, SymbolType type);
};


#endif //COMPILERPROJECT_SYMBOL_H
