#include <iostream>

int int_pairs(int* const arr, const int size);
int* counting_merge(int* const arr_one,
                    const int size_one, 
                    int* const arr_two,
                    const int size_two,
                    int* cnt);
int* counting_sort(int* const arr, const int size, int* cnt);


int main()
{
    const int arr_size = 10;
    int* arr {new int[arr_size]{9, 1, 4, 7, 2, 8, 5, 6, 3, 0}};

    int cnt = 0;
    const int example = int_pairs(arr, arr_size);
    arr = counting_sort(arr, arr_size, &cnt);

    std::cout
        << "Количество интересных пар, найденных быстрым алгоритмом: "
        << cnt
        << "\nЭталонное количество пар: "
        << example;

    return 0;
}


int int_pairs(int* const arr, const int size) {
    int cnt = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                ++cnt;
            }
        }
    }

    return cnt;
}


int* counting_merge(int* const arr_one,
                    const int size_one, 
                    int* const arr_two,
                    const int size_two,
                    int* cnt)
{
    int* res = new int[size_one + size_two];
    int i = 0, j = 0, k = 0;
    int counter = 0;

    while (i < size_one && j < size_two) {
        if (arr_one[i] <= arr_two[j]) {
            res[k] = arr_one[i];
            ++i, ++k;
        } else {
            res[k] = arr_two[j];
            counter += (size_one - i);
            ++j, ++k;
        }
    }

    while (i < size_one) {
        res[k] = arr_one[i];
        ++i, ++k;
    }
    
    while (j < size_two) {
        res[k] = arr_two[j];
        ++j, ++k;
    }
    (*cnt) += counter;

    return res;
    delete[] res;
}


int* counting_sort(int* const arr, const int size, int* cnt) {
    if (size <= 1) {
        return arr;
    }

    const int mid = size / 2;
    int* arr_one = counting_sort(arr, mid, cnt);
    int* arr_two = counting_sort(arr + mid, size - mid, cnt);

    return counting_merge(arr_one, mid, arr_two, size - mid, cnt);
}
