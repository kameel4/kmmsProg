#include <gtest/gtest.h>

#include "vector.hpp"

using biv::Vector;

/*
test adding values 

i think it's has to be tested first as
any of other methods require vectors
filled with values. Developing this idea, im gonna 
use assert_eq testing pushing and expect_eq for others
methods
*/

TEST(Vector, test_pushing_back) {
	Vector<int> int_vector;
	int int_arr[5] = {1, 2, 3, 4, 5};
	Vector<int> expected_int_vector(int_arr, sizeof(int_arr) / sizeof(int_arr[0]));
	for (int i = 1; i<6; i++) int_vector.push_back(i);

	Vector<string> string_vector;
	string string_arr[2] = {"Vanya", "Sasha"};
	Vector<string> expected_string_vector(string_arr, sizeof(string_arr) / sizeof(string_arr[0]));
	string_vector.push_back("Vanya");
	string_vector.push_back("Sasha");

	ASSERT_EQ(int_vector, expected_int_vector);
	ASSERT_EQ(string_vector, expected_string_vector);
}

TEST(Vector, test_inserting){
	int to_insert_arr[4] = {1, 2, 4, 5};
	Vector<int> to_insert(to_insert_arr, sizeof(to_insert_arr)/sizeof(to_insert_arr[0]));
	int expected_arr[5] = {1, 2, 3, 4, 5};
	Vector<int> expected(expected_arr, sizeof(expected_arr)/sizeof(expected_arr[0]));
	bool has_inserted;

	has_inserted = to_insert.insert(2, 3);
	// to_insert.print();

	EXPECT_EQ(to_insert, expected);
	EXPECT_EQ(has_inserted, true);

	has_inserted = to_insert.insert(69, 69);

	EXPECT_EQ(has_inserted, false);

}

TEST(Vector, test_getting_size){
	EXPECT_EQ(Vector<int>().get_size(), 0);
	int length_five[5] = {56, 8, 9, 76, 38};
	EXPECT_EQ(Vector<int>(length_five, sizeof(length_five)/sizeof(length_five[0])).get_size(), 5);
}

TEST(Vector, test_item_presence){
	int arr[5] = {1, 2, 3, 4, 5};
	Vector<int> vec(arr, 5);

	EXPECT_EQ(vec.has_item(3), true);
	EXPECT_EQ(vec.has_item(69), false);
}

TEST(Vector, test_removing_first_elem){
	int arr[5] = {1, 2, 3, 4, 5};
	Vector<int> vec(arr, 5);

	// removing an existing elem
	bool is_removed = vec.remove_first(3);
	EXPECT_EQ(is_removed, true);
	int expected_arr1[4] = {1, 2, 4, 5};
	Vector<int> expected_vec1(expected_arr1, 4);
	EXPECT_EQ(vec, expected_vec1);

	// removing a non-existing elem
	is_removed = vec.remove_first(10);
	EXPECT_EQ(is_removed, false);
	EXPECT_EQ(vec, expected_vec1);

	// removing the first elem
	is_removed = vec.remove_first(1);
	EXPECT_EQ(is_removed, true);
	int expected_arr2[3] = {2, 4, 5};
	Vector<int> expected_vec2(expected_arr2, 3);
	EXPECT_EQ(vec, expected_vec2);

	// removing the last
	is_removed = vec.remove_first(5);
	EXPECT_EQ(is_removed, true);
	int expected_arr3[2] = {2, 4};
	Vector<int> expected_vec3(expected_arr3, 2);
	EXPECT_EQ(vec, expected_vec3);

}

TEST(Vector, test_resizing){
	Vector<int> vec;
	EXPECT_EQ(vec.get_capacity(), 32);
	// cout<<"start capacity: "<<vec.get_capacity()<<endl;
	for (int i = 0; i<33; i++){
		vec.push_back(i);
	}
	EXPECT_EQ(vec.get_capacity(), 64);

	// cout<< "after pushing capacity: "<< vec.get_capacity()<<endl;
	for (int i = 0; i < 10; i++){
		vec.remove_first(i);
	}
	EXPECT_EQ(vec.get_capacity(), 32);
	// cout<< "after removing capacity: "<< vec.get_capacity()<<endl;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
