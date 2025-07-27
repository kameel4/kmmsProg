target_sources(linear_sort_lib
    PRIVATE
        linearSort.cpp
    PUBLIC
        linearSort.hpp)

target_include_directories(linear_sort_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})