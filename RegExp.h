//
// Created by Abdallah on 11/29/2022.
//
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

#ifndef COMPILERPROJECT_REGEXP_H
#define COMPILERPROJECT_REGEXP_H

enum RegExpType { concatenation, disjunction, kleeneClosure, positiveClosure, range ,terminal, epsilon};


class RegExp {
private:
    // These constructors are private because they expose implementation details
    // Instead you should use parseRegExp(string)
    RegExp(std::vector<RegExp> operands, RegExpType type): operands(std::move(operands)), type(type) {};
    explicit RegExp(char terminal): terminal(terminal) {
        type = RegExpType::terminal;
    };

//private: public for testing purposes
public:
    // marking these as static to separate them from the class variables
    static RegExp parseRegExp(std::string str);
    static RegExp epsilon(){
        RegExp regExp;
        regExp.type = RegExpType::epsilon;
        return regExp;
    };
    static std::vector<std::string> getTopLevelDisjunction(std::string str);
    static std::vector<std::string> getTopLevelConcatenation(std::string str);
    static std::vector<std::string> getTopLevelClosure(std::string str);
    static std::vector<std::string> getRange(std::string str);
    RegExp()= default;

    // Helpers:
    static std::vector<std::string> getTopLevelString(char delimiter, std::string str);
    std::vector<std::string> toString();


public:
    RegExpType type;
    std::vector<RegExp> operands;
    char terminal=0;
};


#endif //COMPILERPROJECT_REGEXP_H
