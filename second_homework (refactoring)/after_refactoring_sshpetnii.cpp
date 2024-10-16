#include <cmath>
#include <iostream>

void print_sequence(const char* const comment, float* sequence, const int size);
void generate_sequence(float* sequence, const int size, float* sum);

int main()
{
    const int seq_size = 10;
    float* first_sequence = new float[seq_size]; 
    float* second_sequence = new float[seq_size];
    float* third_sequence = new float[10];
    float sum_of_first_seq = 0, sum_of_second_seq = 0, sum_of_third_seq = 0;

    generate_sequence(first_sequence, seq_size, &sum_of_first_seq);
    generate_sequence(second_sequence, seq_size, &sum_of_second_seq);
    generate_sequence(third_sequence, seq_size, &sum_of_third_seq);

    print_sequence("Первая последовательность:", first_sequence, seq_size);
    std::cout <<"Среднее первой последовательности = " << sum_of_first_seq / seq_size << std::endl;
    std::cout << std::endl;

    print_sequence("Вторая последовательность:", second_sequence, seq_size);
    std::cout <<"Среднее второй последовательности = " << sum_of_second_seq / seq_size << std::endl;
    std::cout << std:: endl;

    print_sequence("Третья последовательность:", third_sequence, seq_size);
    std::cout <<"Среднее третьей последовательности = " << sum_of_third_seq / seq_size << std::endl;
    std::cout << std::endl;

    delete[] first_sequence, second_sequence, third_sequence;
    return 0;
}

void print_sequence(const char* const comment, float* sequence, const int size) {
    const char space = ' ';
    std::cout << comment << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << space << sequence[i];
    }
    std::cout << std::endl;
}

void generate_sequence(float* sequence, const int size, float* sum) {
    for (int i = 0; i < size; ++i) {
        sequence[i] = rand() % 10;
        *sum += sequence[i];
    }
}
