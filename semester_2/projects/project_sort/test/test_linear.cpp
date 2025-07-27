#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linearSort.hpp"




TEST(VectorsEqual, AnyElementsCount) {
    std::vector<long long> actual = {1, 8, 2, 5, 3, 11};
    radixSort(actual, 10);
    std::vector<long long> expected = {1, 2, 3, 5, 8, 11};
    ASSERT_EQ(expected.size(), actual.size())
        << "Vectors have different sizes";
    
    for (size_t i = 0; i < actual.size(); ++i) {
        ASSERT_EQ(expected[i], actual[i])
            << "Vectors are not equal";
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
