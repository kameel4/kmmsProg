add_executable(ProjectSort_test sort_unittest.cpp)

target_link_libraries(${PROJECT_NAME}_test gtest_main)

add_test(NAME ProjectSort_test COMMAND ProjectSort_test)
