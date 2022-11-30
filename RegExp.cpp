//
// Created by Abdallah on 11/29/2022.
//

#include <iostream>
#include "RegExp.h"



RegExp::RegExp(std::string str) {
    str = RegExp::removeLeadingAndTrailingSpaces(str);

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

    std::vector<std::string> closureOperands = RegExp::getTopLevelClosure(str);

    if (closureOperands.size() > 1) {
        std::string closureType = closureOperands.back();
        if (closureType == "+")
            type = RegExpType::positiveClosure;
        else if (closureType == "*")
            type = RegExpType::kleeneClosure;
        operands.emplace_back(closureOperands.front());
        return;
    }

    std::vector<std::string> rangeOperands = RegExp::getRange(str);

    if (rangeOperands.size() > 1) {
        type = RegExpType::range;
        for (const auto& operand: rangeOperands) {
            operands.emplace_back(operand);
        }
        return;
    }

    type = RegExpType::terminal;
    terminal = str[0];
}


std::vector<std::string> RegExp::getTopLevelDisjunction(std::string str) {
    return getTopLevelString('|', str);
}

std::vector<std::string> RegExp::getTopLevelConcatenation(std::string str) {
    return getTopLevelString(' ', str);
}

std::vector<std::string> RegExp::getTopLevelString(char delimiter, std::string str){
    str = removeEnclosingBrackets(str);
    std::vector<std::string> operands;

    std::string temp = "";
    int openBrackets = 0;

    for (int i = 0;i < str.size();i++) {
        if (str[i] == delimiter && openBrackets == 0) {
            if (!emptyString(temp))
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

    if (!emptyString(temp))
        operands.push_back(temp);
    return operands;
}

std::vector<std::string> RegExp::getTopLevelClosure(std::string str) {
    // TODO
    std::vector<std::string> operands;
    int n = str.size();
    int endOfString;
    std::string closureType;
    std::string temp;

    if (str.front() == '(' && str[n-2] == ')'){
        endOfString = n-3;
        closureType = std::string(1,str[n-1]);
        temp = str.substr(1, endOfString);
        operands.push_back(temp);
        // Type of closure will be returned in the vector.
        operands.push_back(closureType);
        return operands;
    }
    else if (str.back() == '+' || str.back() == '*') {
        endOfString = n-1;
        temp = str.substr(0, endOfString);
        operands.push_back(temp);
        closureType = str.back();
        // Type of closure will be returned in the vector.
        operands.push_back(closureType);
        return operands;
    }
    operands.push_back(str);
    return operands;
}

std::vector<std::string> RegExp::getRange(std::string str) {
    std::vector<std::string> rangeOperands;

    if (str[1] == '-') {
        int start = str.front();
        int end = str.back();
        for (int i = start; i <= end; ++i) {
            rangeOperands.push_back(std::string(1, i));
        }
        return rangeOperands;
    }
    rangeOperands.push_back(str);
    return rangeOperands;
}

std::string RegExp::removeEnclosingBrackets(std::string str) {
    while (str.front() == '(' && str.back() == ')')
        str = str.substr(1, str.size()-2);
    return str;
}

std::string RegExp::removeLeadingAndTrailingSpaces(std::string str) {
    int start=0;
    int end = str.size();
    while (start< str.size() && str[start] == ' ')
        start++;

    while (end > 0 && str[end-1] == ' ')
        end--;
    return str.substr(start, end-start);
}

/**
 * String containing only whitespaces
 */
bool RegExp::emptyString(std::string str) {
    return str.find_first_not_of(' ') == std::string::npos;
}


