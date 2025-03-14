cmake_minimum_required(VERSION 3.30)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/SyntaxAnalyzer)

add_executable(Calculator main.cpp
        SyntaxAnalyzer/syntaxAnalyzer.cpp
        SyntaxAnalyzer/syntaxAnalyzer.h)
