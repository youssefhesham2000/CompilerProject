//
// Created by Abdallah on 11/29/2022.
//

#include <iostream>
#include "RegExp.h"



RegExp::RegExp(std::string str) {
    std::vector<std::string> disjunctionOperands = RegExp::getTopLevelDisjunction(str);

    // If there are multiple operands separated by |, parse each of them
    if (disjunctionOperands.size() > 1){
        type = RegExpType::disjunction;

        for (const auto& operand: disjunctionOperands) {
            operands.emplace_back(operand);
        }
        return;
    }

    std::vector<std::string> concatenationOperands = RegExp::getTopLevelConcatenation(str);

    if (concatenationOperands.size() > 1){
        type = RegExpType::concatenation;

        for (const auto& operand: concatenationOperands) {
            operands.emplace_back(operand);
        }
        return;
    }

    // TODO: implement ()*, ()+, and ()
    type = RegExpType::terminal;
    terminal = str[0];
}


std::vector<std::string> RegExp::getTopLevelDisjunction(std::string str) {
    str = removeEnclosingBrackets(str);
    std::vector<std::string> operands;

    std::string temp = "";
    int openBrackets = 0;

    for (int i = 0;i < str.size();i++) {
        if (str[i] == '|' && openBrackets == 0) {
            operands.push_back(temp);
            temp = "";
        } else if (str[i] == '\\') {
            // This is a \ followed by a literal, append both
            temp += '\\';
            temp += str[i + 1];
            i++;
        } else {
            if (str[i] == '(') {
                openBrackets++;
            } else if (str[i] == ')') {
                openBrackets--;
            }

            temp += str[i];
        }
    }

    if (!temp.empty())
        operands.push_back(temp);
    return operands;
}

std::vector<std::string> RegExp::getTopLevelConcatenation(std::string str) {
    // TODO
    return std::vector<std::string>();
}

std::vector<std::string> RegExp::getTopLevelClosure(std::string str) {
    // TODO
    return std::vector<std::string>();
}

std::string RegExp::removeEnclosingBrackets(std::string str) {
    while (str.front() == '(' && str.back() == ')')
        str = str.substr(1, str.size()-2);
    return str;
}


