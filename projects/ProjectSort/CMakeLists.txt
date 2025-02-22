# projectSort/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(ProjectSort LANGUAGES CXX)

set(SOURCES
    src/main.cpp
    src/linearSort.cpp
    src/linearSort.hpp
    )



add_executable(ProjectSort ${SOURCES})