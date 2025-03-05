#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "my_algorithms.hpp"

TEST(SortingTest, CountingSortTest) {
    const int arr_size = 10;
    int arr[arr_size] = {9, 1, 4, 7, 2, 8, 5, 6, 3, 0};

    int cnt = 0;
    const int example = counters::int_pairs(arr, arr_size);
    int* sorted_arr = counters::merge::counting_sort(arr, arr_size, &cnt);

    EXPECT_EQ(cnt, example);
    for (int i = 0; i < arr_size - 1; ++i) {
        EXPECT_LE(sorted_arr[i], sorted_arr[i + 1]);
    }

    delete[] sorted_arr;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
