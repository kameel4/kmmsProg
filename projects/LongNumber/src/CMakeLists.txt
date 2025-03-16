target_sources(long_number_lib
    PRIVATE
        long_number.cpp
    PUBLIC
        long_number.hpp)

target_include_directories(long_number_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
    