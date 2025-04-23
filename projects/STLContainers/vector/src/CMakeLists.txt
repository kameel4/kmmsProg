target_sources(vector_lib
    PRIVATE
        vector.cpp
    PUBLIC
        vector.hpp)

target_include_directories(vector_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})