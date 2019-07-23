#include <iostream>
#include <chrono>
#include <cmath>

//2а. Итеративный (n умножений)
double iter(double a, unsigned long b) {
    double ans = 1;
    for (unsigned long i = 0; i < b; ++i) {
        ans *= a;
    }
    return ans;
}

//2b. Через степень двойки с домножением
double pow2(double a, unsigned long b) {
    unsigned long power = 1;
    double ans = a;

    while (power < b / 2) {
        ans *= ans;
        power *= 2;
    }
    while (power < b) {
        ans *= a;
        ++power;
    }
    return ans;
}

//2c. Через двоичное разложение показателя степени.
double fast(double a, unsigned long b) {
    double ans = 1;

    while (b > 1) {
        if (b % 2 == 1) {
            ans *= a;
        }
        a *= a;
        b /= 2;
    }
    if (b > 0) ans *= a;
    return ans;
}

int main() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    auto ans1 = iter(1.0000001, 1000000000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "iter(1.0000001, 1000000000) = " << ans1 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans2 = pow2(1.0000001, 1000000000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "pow2(1.0000001, 1000000000) = " << ans2 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans3 = fast(1.0000001, 1000000000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "fast(1.0000001, 1000000000) = " << ans3 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;
}