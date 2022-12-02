//
// Created by Abdallah on 11/29/2022.
//

#include <iostream>
#include "RegExp.h"
#include "RulesParser.h"
#include "StringUtils.h"


RegExp RegExp::parseRegExp(std::string str) {
    str = StringUtils::removeLeadingAndTrailingSpaces(str);
    str = StringUtils::removeEnclosingBrackets(str);

    std::vector<RegExp> operands;
    RegExpType type;

    // Single terminal or epsilon
    if (str.size() == 1) {
        return RegExp(str[0]);
    }

    if (str.size() == 2 && str[0] == '\\') {
        if (str[1] == 'L')
            return RegExp::epsilon();
        return RegExp(str[1]);
    }

    std::vector<std::string> disjunctionOperands = RegExp::getTopLevelDisjunction(str);

    // If there are multiple operands separated by |, parse each of them
    if (disjunctionOperands.size() > 1){
        type = RegExpType::disjunction;
        for (const auto& operand: disjunctionOperands) {
            operands.push_back(parseRegExp(operand));
        }

        return RegExp(operands, type);
    }

    std::vector<std::string> concatenationOperands = RegExp::getTopLevelConcatenation(str);

    if (concatenationOperands.size() > 1){
        type = RegExpType::concatenation;
        for (const auto& operand: concatenationOperands) {
            operands.push_back(parseRegExp(operand));
        }
        return RegExp(operands, type);
    }

    std::vector<std::string> closureOperands = RegExp::getTopLevelClosure(str);

    if (closureOperands.size() > 1) {
        std::string closureType = closureOperands.back();
        if (closureType == "+")
            type = RegExpType::positiveClosure;
        else if (closureType == "*")
            type = RegExpType::kleeneClosure;
        operands.push_back(parseRegExp(closureOperands.front()));
        return RegExp(operands, type);
    }

    std::vector<std::string> rangeOperands = RegExp::getRange(str);

    if (rangeOperands.size() > 1) {
        type = RegExpType::range;
        for (const auto& operand: rangeOperands) {
            operands.push_back(parseRegExp(operand));
        }
        return RegExp(operands, type);
    }


    // Check if this a regular definition
    auto regularDefinition = RulesParser::regularDefinitionsMap.find(str);
    if (regularDefinition != RulesParser::regularDefinitionsMap.end()) {
        // Token already exists
        return regularDefinition->second;
    }

    // Finally, this is a sequence of terminals
    // Consider it as a concatenation
    type = concatenation;
    for (int i = 0;i < str.size();i++) {
       if (str[i] == '\\'){
           if (str[i+1] == 'L')
               operands.push_back(RegExp::epsilon());
           else
               operands.push_back(RegExp(str[i+1]));

           i++;
       }
       else operands.push_back(RegExp(str[i]));
    }

    return RegExp(operands, type);
}


std::vector<std::string> RegExp::getTopLevelDisjunction(std::string str) {
    return getTopLevelString('|', str);
}

std::vector<std::string> RegExp::getTopLevelConcatenation(std::string str) {
    return getTopLevelString(' ', str);
}

std::vector<std::string> RegExp::getTopLevelString(char delimiter, std::string str){
    std::vector<std::string> operands;

    std::string temp = "";
    int openBrackets = 0;

    for (int i = 0;i < str.size();i++) {
        if (str[i] == delimiter && openBrackets == 0) {
            if (!StringUtils::emptyString(temp))
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

    if (!StringUtils::emptyString(temp))
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

RegExp RegExp::parseKeyWord(std::string str) {
    std::string temp = StringUtils::removeLeadingAndTrailingSpaces(str);
    std::vector<RegExp> operands;
    RegExpType type =RegExpType::concatenation;
    for(int i = 0; i < temp.length(); i++) {
        operands.push_back(parseRegExp(std::string(1, temp[i])));
    }
    return RegExp(operands,type);
}

RegExp RegExp::parsePunctuations(std::string str) {
    str = StringUtils::removeLeadingAndTrailingSpaces(str);
    if (str.length()>1)
        throw std::invalid_argument(str);
    return parseRegExp(str);
}

std::vector<std::string> RegExp::toString() {
    std::vector<std::string> result;

    switch (type) {
        case disjunction:
            result.push_back("OR");
            break;
        case concatenation:
            result.push_back("CONCAT");
            break;
        case kleeneClosure:
            result.push_back("*");
            break;
        case positiveClosure:
            result.push_back("+");
            break;
        case range:
            result.push_back("RANGE");
            break;
        case RegExpType::terminal:
            result.emplace_back(1, terminal);
            return result;
        case RegExpType::epsilon:
            result.push_back("EPISLON");
            return result;
    }

    for (RegExp operand: operands) {
        for (std::string line : operand.toString()) {
            result.push_back("\t" + line);
        }
    }

    return result;
}
