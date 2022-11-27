cmake_minimum_required(VERSION 3.17)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilerProject main.cpp RulesParser.h RulesParser.cpp )