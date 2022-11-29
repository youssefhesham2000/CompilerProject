cmake_minimum_required(VERSION 3.17)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilerProject main.cpp RulesParser.h RulesParser.cpp Pattern.cpp Pattern.h DFA.cpp DFANode.h TransitionTable.cpp TransitionTable.h Token.cpp Token.h Minimizer.cpp Minimizer.h)