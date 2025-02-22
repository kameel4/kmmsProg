cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=cp866")


project(MultiLevelMenu LANGUAGES CXX)

set(SOURCES
    src/main.cpp
    src/actions.cpp
    )

add_executable(MultiLevelMenu ${SOURCES})

target_include_directories(MultiLevelMenu
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
