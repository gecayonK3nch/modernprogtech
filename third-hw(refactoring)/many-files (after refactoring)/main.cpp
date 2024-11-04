#include "my_algorithms.hpp"
#include <iostream>

int main()
{
    const int arr_size = 10;
    int* arr {new int[arr_size]{9, 1, 4, 7, 2, 8, 5, 6, 3, 0}};

    int cnt = 0;
    const int example = counters::int_pairs(arr, arr_size);
    arr = counters::merge::counting_sort(arr, arr_size, &cnt);

    std::cout << cnt << " " << example;

    return 0;
}
