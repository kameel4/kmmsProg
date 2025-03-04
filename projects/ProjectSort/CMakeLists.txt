# projectSort/CMakeLists.txt

project(ProjectSort LANGUAGES CXX)

add_library(linear_sort_lib "")

add_subdirectory(src)
add_subdirectory(test)

# set(SOURCES
#     src/linearSort/linearSort.cpp
#     )



# add_executable(ProjectSort ${SOURCES})

# # add_executable(${PROJECT_NAME}_test test/sort_unittest.cpp)

# # Link test executable to Google Test library
# target_link_libraries(${PROJECT_NAME}_test gtest_main linearSort)



# # Add test
# add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)

