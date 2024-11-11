#include <iostream>

int main()
{
    const int arr[] = {3, 6, 5, 9, 10};
    const char space = ' ';
    int min = 11, max = 0;

    for (int el : arr) {
        if (el <= min) {
            min = el;
        }
        if (el >= max) {
            max = el;
        }
    }
    const float res = float(max) / min;

    std::cout << "Данный массив:" << std::endl;
    for (int el : arr) {
        std::cout<< el << space;
    }
    std::cout << std::endl
              << "Максимальный элемент: " << max
              << "\nМинимальный элемент: " << min
              << "\nМаксимальный элемент больше минимального в " << res << " раза";

    return 0;
}
