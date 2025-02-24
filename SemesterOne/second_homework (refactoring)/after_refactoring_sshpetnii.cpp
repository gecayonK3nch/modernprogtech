#include <iostream>

float calculate_average(const int sum, const int count);
void generate_arr(int* arr, const int size, int* sum);
void print_arr(int* arr, const int size);

int main()
{
    const int arr_size = 10;
    const int arr_from = 1;
    const int arr_to = 3;

    for (int i = arr_from; i <= arr_to; ++i) {
        int* arr = new int[arr_size]; 
        int sum_of_arr = 0;

        generate_arr(arr, arr_size, &sum_of_arr);
        const float average = calculate_average(sum_of_arr, arr_size);

        std::cout << "Последовательность номер " << i << std::endl;
        print_arr(arr, arr_size);
        std::cout << "Среднее этой последовательности = " << average << std::endl;
        std::cout << std::endl;
        delete[] arr;
    }

    return 0;
}

float calculate_average(const int sum, const int count) {
    return float(sum) / count;
}

void generate_arr(int* arr, const int size, int* sum) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10;
        *sum += arr[i];
    }
}

void print_arr(int* arr, const int size) {
    static const char space = ' ';

    for (int i = 0; i < size; ++i) {
        std::cout << space << arr[i];
    }
    std::cout << std::endl;
}
