//
// Created by mohamed on 12/16/2022.
//

#include "Symbol.h"
Symbol::Symbol(std::string symbol, SymbolType type) {
    if (symbol == "\\L") {
        this->symbol = epsilonSymbol.symbol;
        this->type = epsilonSymbol.type;
        return;
    }
    this->symbol = symbol;
    this-> type = type;

}