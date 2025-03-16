set(SOURCES
    test_operators.cpp
)

add_executable(test_operators ${SOURCES})

target_link_libraries(test_operators
    gtest_main
    gmock_main
    long_number_lib
)

add_test(test_operators test_operators)
