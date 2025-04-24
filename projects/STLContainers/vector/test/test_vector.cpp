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

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
