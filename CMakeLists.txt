cmake_minimum_required(VERSION 3.17)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilerProject main.cpp Phase1/RulesParser.h Phase1/RulesParser.cpp Phase1/Pattern.cpp Phase1/Pattern.h Phase1/DFA.cpp Phase1/DFANode.h Phase1/TransitionTable.cpp Phase1/TransitionTable.h Phase1/Token.cpp Phase1/Token.h Phase1/Minimizer.cpp Phase1/Minimizer.h Phase1/RegExp.cpp Phase1/RegExp.h StringUtils.h Phase1/StringUtils.cpp Phase1/NFANode.cpp Phase1/NFANode.h Phase1/NFA.cpp Phase1/NFA.h Phase1/NFAConvertor.cpp Phase1/NFAConvertor.h Phase1/RegExpGenerator.cpp Phase1/RegExpGenerator.h Phase1/SubsetConstructor.cpp Phase1/SubsetConstructor.h Phase2/Symbol.cpp Phase2/Symbol.h Phase2/Production.cpp Phase2/Production.h Phase2/ParsingTable.cpp Phase2/ParsingTable.h Phase2/HashFunction.h Phase2/SetBuilder.cpp Phase2/SetBuilder.h)