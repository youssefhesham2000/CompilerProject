
#ifndef COMPILERPROJECT_SYMBOL_H
#define COMPILERPROJECT_SYMBOL_H


#include <string>
#include <cmath>

enum class SymbolType { terminal, nonTerminal};

class Symbol  {

public:
    Symbol()=default;
    SymbolType type;
    std::string symbol;
    bool operator==(const Symbol& s) const{
        return symbol == s.symbol && type == s.type;
    }

    bool operator!=(const Symbol& s) const{
        return symbol != s.symbol || type != s.type;
    }

    bool operator<(const Symbol& s) const{
        if (*this == s)
            return false;
        return symbol < s.symbol;
    }

    Symbol(std::string, SymbolType type);

};

const Symbol epsilonSymbol = Symbol("\0", SymbolType::terminal);
const Symbol endOfParsingSymbol = Symbol("$", SymbolType::terminal);

namespace std {
    template <>
    struct hash<Symbol> {
        auto operator()(const Symbol &s) const -> size_t {
            return hash<string>{}(s.symbol);
        }
    };
}





#endif //COMPILERPROJECT_SYMBOL_H
