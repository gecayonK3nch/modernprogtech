#include <format>
#include <iostream>
#include <map>

void generate_sequence(float* sequence, const int size, float* sum);
void print_sequence(const char* const comment, float* sequence, const int size);
int calculate_ariphmetic_mean(const float sum, const int count);

int main()
{
    const int seq_size = 10;
    const char* name_of_seq[3] = {
        "Первая последовательность:",
        "Вторая последовательность:",
        "Третья последовательность:"
    };

    for (int i = 1; i <= 3; ++i) {
        float* sequence = new float[seq_size]; 
        float sum_of_seq = 0;
        float ariphmetic_mean = calculate_ariphmetic_mean(sum_of_seq, seq_size);

        generate_sequence(sequence, seq_size, &sum_of_seq);

        print_sequence(name_of_seq[i - 1], sequence, seq_size);
        std::cout << "Среднее этой последовательности = " << ariphmetic_mean << std::endl;
        std::cout << std::endl;
        delete[] sequence;
    }

    delete[] name_of_seq;
    return 0;
}

void print_sequence(const char* const comment, float* sequence, const int size) {
    static const char space = ' ';

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

int calculate_ariphmetic_mean(const float sum, const int count) {
    return sum / count;
}
