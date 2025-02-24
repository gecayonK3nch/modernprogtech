#ifndef MY_ALGORITHMS_HPP
#define MY_ALGORITHMS_HPP

namespace counters {
    namespace merge {
        int* counting_merge(int* const arr_one,
                    const int size_one, 
                    int* const arr_two,
                    const int size_two,
                    int* cnt);
        int* counting_sort(int* const arr, const int size, int* cnt);
    }
    int int_pairs(int* const arr, const int size);
}

#endif
