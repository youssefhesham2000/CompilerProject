//
// Created by Abdallah on 11/29/2022.
//
#include <utility>
#include <vector>
#include <string>

#ifndef COMPILERPROJECT_REGEXP_H
#define COMPILERPROJECT_REGEXP_H

enum RegExpType { concatenation, disjunction, kleeneClosure, positiveClosure, range ,terminal };

class RegExp {
//private: public for testing purposes
public:

    // marking these as static to separate them from the class variables
    static std::vector<std::string> getTopLevelDisjunction(std::string str);
    static std::vector<std::string> getTopLevelConcatenation(std::string str);
    static std::vector<std::string> getTopLevelClosure(std::string str);
    static std::vector<std::string> getRange(std::string str);
    RegExp(std::vector<RegExp> operands, RegExpType type): operands(std::move(operands)), type(type) {};

    // Helpers:
    static std::vector<std::string> getTopLevelString(char delimiter, std::string str);
    static std::string removeEnclosingBrackets(std::string str);
    static bool emptyString(std::string str);
    static std::string removeLeadingAndTrailingSpaces(std::string str);


public:
    RegExpType type;
    std::vector<RegExp> operands;
    char terminal{};
    explicit RegExp(std::string str);

};


#endif //COMPILERPROJECT_REGEXP_H
