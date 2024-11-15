#include <iostream>
#include <limits.h>

int main()
{
    const int arr[] = {3, 6, 5, 9, 10};
    int min = INT_MAX, max = INT_MIN;

    for (int el : arr) {
        if (el <= min) {
            min = el;
        }
        if (el >= max) {
            max = el;
        }
    }
    const float res = float(max) / min;

    const char space = ' ';
    std::cout << "Данный массив:" << std::endl;
    for (int el : arr) {
        std::cout<< el << space;
    }
    std::cout << std::endl
              << "Максимальный элемент: " << max << std::endl
              << "Минимальный элемент: " << min << std::endl
              << "Максимальный элемент больше минимального в " << res << " раза";

    return 0;
}
