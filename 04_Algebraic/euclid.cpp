#include <iostream>
#include <chrono>

//1a. Через вычитание
unsigned long sub(unsigned long a, unsigned long b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

//1b. Через остаток
unsigned long rem(unsigned long a, unsigned long b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a != 0 ? a : b;
}

int main() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    auto ans1 = sub(125, 5);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "sub(125,5) = " << ans1 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans2 = sub(1234567890, 12);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "sub(1234567890,12) = " << ans2 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans3 = rem(125, 5);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "rem(125,5) = " << ans3 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans4 = rem(1234567890, 12);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "rem(1234567890,12) = " << ans4 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    return 0;
}