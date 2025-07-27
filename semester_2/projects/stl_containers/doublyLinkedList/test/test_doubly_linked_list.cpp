#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using biv::DoublyLinkedList;


TEST(DoublyLinkedListTest, test_pushing_back) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int expected_arr[3] = {1, 2, 3};
    DoublyLinkedList<int> expected_list(expected_arr, 3);

    EXPECT_EQ(list, expected_list);

}

TEST(DoublyLinkedListTest, test_item_presence) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_TRUE(list.has_item(1));
    EXPECT_TRUE(list.has_item(2));
    EXPECT_TRUE(list.has_item(3));
    EXPECT_FALSE(list.has_item(4));
    EXPECT_FALSE(list.has_item(69));

    DoublyLinkedList<int> empty_list;
    EXPECT_FALSE(empty_list.has_item(1));
}

TEST(DoublyLinkedListTest, test_size) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.get_size(), 3);

    DoublyLinkedList<string> empty_text;

    EXPECT_EQ(empty_text.get_size(), 0);
}

TEST(DoublyLinkedListTest, test_remove_first) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_FALSE(list.remove_first(69));
    EXPECT_FALSE(list.has_item(69));

    EXPECT_TRUE(list.remove_first(1));
    EXPECT_FALSE(list.has_item(1));

    EXPECT_TRUE(list.remove_first(2));
    EXPECT_FALSE(list.has_item(2));

    EXPECT_TRUE(list.remove_first(3));
    EXPECT_FALSE(list.has_item(3));

    EXPECT_FALSE(list.remove_first(1));
    EXPECT_FALSE(list.has_item(1));
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
