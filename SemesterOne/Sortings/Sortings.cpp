#include <iostream>
#include <algorithm>

void bubble_sort(int* const arr, const size_t size, bool reverse = false);
void bubble_sort_no_swap(int* const arr, const size_t size, bool reverse = false);
void odd_even_sort(int* const arr, const size_t size, bool reverse = false);

void bubble_sort(int* const arr, const size_t size, bool reverse) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (reverse ? arr[j] < arr[j + 1] : arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_no_swap(int* const arr, const size_t size, bool reverse) {
    bool swapped;
    int i = 0;
    do {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (reverse ? arr[j] < arr[j + 1] : arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        ++i;
    } while (swapped);
}

void odd_even_sort(int* const arr, const size_t size, bool reverse) {
    bool swapped;
    int i = 0;
    do {
        swapped = false;
        for (int j = i % 2; j < size - 1; j += 2) {
            if (reverse ? arr[j] < arr[j + 1] : arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        ++i;
    } while (swapped);
}

bool test(int* const arr, const size_t size, void (*func)(int* const, const size_t, bool)) {
    int* arr_copy = new int[size];
    for (int i = 0; i < size; i++) {
        arr_copy[i] = arr[i];
    }

    func(arr_copy, size, false);
    std::sort(arr, arr + size);

    for (int i = 0; i < size; i++) {
        if (arr[i] != arr_copy[i]) {
            delete[] arr_copy;
            return false;
        }
    }
    delete[] arr_copy;
    return true;
}

int main() {
    int arr[] = { 5, 2, 3, 1, 4 };
    const size_t size = sizeof(arr) / sizeof(arr[0]);

    if (test(arr, size, bubble_sort) && test(arr, size, bubble_sort_no_swap) && test(arr, size, odd_even_sort)) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }

    return 0;
}
