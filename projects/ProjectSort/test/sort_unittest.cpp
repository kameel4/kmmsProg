#include "linearSort/linearSort.hpp"
#include "gtest/gtest.h"




TEST(LinearSortTest, isCorrectSort) {
    vector <long long> unsorted1 = {3, 5, 1, 2, 6, 4, 7, 9, 8};
    radixSort(unsorted1, 10);
    EXPECT_EQ(unsorted1, (vector<long long>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(LinearSortTest, negativeNumbers) {
    vector <long long> unsorted2 = {-3, -5, -1, -2, -6, -4, -7, -9, -8};
    EXPECT_EQ(unsorted2, (vector<long long>{-9, -8, -7, -6, -5, -4, -3, -2, -1}));
}

TEST(LinearSortTest, repeatedNumbers){
    vector <long long> unsorted3 = {3, 3, 3, 5, 51, 4, -44, 44, -44};
    EXPECT_EQ(unsorted3, (vector<long long>{-44, -44, -3, 3, 3, 3, 4, 5, 51}));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
