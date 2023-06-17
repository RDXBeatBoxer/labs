#include <iostream>
#include <cstdarg>

int sum(int count, ...) {
    int total = 0;
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        total += num;
    }

    va_end(args);

    return total;
}

int main() {
    int result1 = sum(3, 1, 2, 3);
    std::cout << "Sum of 1, 2, 3: " << result1 << std::endl;

    int result2 = sum(7, 1, 2, 3, 4, 5, 6, 7);
    std::cout << "Sum of 1, 2, 3, 4, 5, 6, 7: " << result2 << std::endl;

    int result3 = sum(11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    std::cout << "Sum of 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11: " << result3 << std::endl;

    return 0;
}