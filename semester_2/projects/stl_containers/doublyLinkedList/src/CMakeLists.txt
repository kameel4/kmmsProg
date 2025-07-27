target_sources(doubly_linked_list_lib
    PRIVATE
        doubly_linked_list.cpp
    PUBLIC
        doubly_linked_list.hpp)

target_include_directories(doubly_linked_list_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})