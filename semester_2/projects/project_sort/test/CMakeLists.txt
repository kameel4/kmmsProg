set(SOURCES
    test_linear.cpp
)

add_executable(test_linear ${SOURCES})
target_link_libraries(test_linear
    gtest_main
    gmock_main
    linear_sort_lib
)

add_test(test_linear test_linear)
