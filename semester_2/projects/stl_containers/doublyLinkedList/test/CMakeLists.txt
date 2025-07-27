set(SOURCES
    doubly_linked_list.cpp
)

add_executable(doubly_linked_list_tests test_doubly_linked_list.cpp templates_doubly_linked_list.cpp)

target_link_libraries(doubly_linked_list_tests 
	gtest 
	doubly_linked_list_lib
)

add_test(doubly_linked_list_tests doubly_linked_list_tests)