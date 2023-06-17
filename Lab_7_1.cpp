#include <iostream>
#include <complex>

// Function for adding integers
int add(int a, int b) {
    return a + b;
}

// Function for adding complex numbers
std::complex<double> add(const std::complex<double>& c1, const std::complex<double>& c2) {
    return c1 + c2;
}

int main() {
    int num1 = 5;
    int num2 = 10;
    int sum = add(num1, num2);
    std::cout << "Sum of integers: " << sum << std::endl;
    
    std::complex<double> c1(2.5, 3.7);
    std::complex<double> c2(1.8, 4.2);
    std::complex<double> complexSum = add(c1, c2);
    std::cout << "Sum of complex numbers: " << complexSum.real() << " + " << complexSum.imag() << "i" << std::endl;

    return 0;
}
