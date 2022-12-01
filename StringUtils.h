//
// Created by Abdallah on 12/1/2022.
//

#ifndef COMPILERPROJECT_STRINGUTILS_H
#define COMPILERPROJECT_STRINGUTILS_H

namespace StringUtils {
    std::string removeEnclosingBrackets(std::string str);

    std::string removeLeadingAndTrailingSpaces(std::string str);

/**
 * String containing only whitespaces
 */
    bool emptyString(std::string str);
}
#endif //COMPILERPROJECT_STRINGUTILS_H
