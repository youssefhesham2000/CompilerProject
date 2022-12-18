#include <string>
#include <stdexcept>
#include "../StringUtils.h"

namespace StringUtils {
    std::string removeEnclosingBrackets(std::string str) {
        while (str.front() == '(' && str.back() == ')')
            str = str.substr(1, str.size() - 2);
        return str;
    }

    std::string removeLeadingAndTrailingSpaces(std::string str) {
        int start = 0;
        int end = str.size();
        while (start < str.size() && str[start] == ' ')
            start++;

        while (end > 0 && str[end - 1] == ' ')
            end--;
        return str.substr(start, end - start);
    }

    std::string removeLeadingAndTrailingSingleQuotes(std::string str) {
        if (str.front() == '\'' && str.back() == '\''){
            return str.substr(1,str.length()-2);
        } else {
            return str;
        }

    }

    bool emptyString(std::string str) {
        return str.find_first_not_of(' ') == std::string::npos;
    }
}