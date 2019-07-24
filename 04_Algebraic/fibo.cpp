#include <iostream>
#include <chrono>
#include <cmath>
#include <array>

//4a. Через рекурсию
unsigned long long rec(int n) {
    if (n <= 2) {
        return 1;
    } else {
        return rec(n - 1) + rec(n - 2);
    }
}

//4b. Через итерацию
double iter(int n) {
    if (n < 2) {
        return 1;
    } else {
        double a = 1;
        double b = 1;
        double f;
        for (int i = 2; i < n; ++i) {
            f = a + b;
            a = b;
            b = f;
        }
        return f;
    }
}

//4c. По формуле золотого сечения
double gold(int n) {
    double f = (1 + std::sqrt(5)) / 2;
    return std::floor(std::pow(f, n) / std::sqrt(5) + .5);
}

//4d. Через умножение матриц (по желанию)
struct matrix {
public:
    matrix() {
        data = {1, 1, 1, 0};
    }

    matrix operator*(matrix &other) {
        matrix ans;
        ans.data[0] = this->data[0] * other.data[0] + this->data[1] * other.data[2];
        ans.data[1] = this->data[0] * other.data[1] + this->data[1] * other.data[3];
        ans.data[2] = this->data[2] * other.data[0] + this->data[3] * other.data[2];
        ans.data[3] = this->data[2] * other.data[1] + this->data[3] * other.data[3];
        return ans;
    }

    std::array<double, 4> data;
};

double matr(int b) {
    matrix ans, one;
    b -= 2;
    while (b > 1) {
        if (b % 2 == 1) {
            ans = ans * one;
        }
        one = one * one;
        b /= 2;
    }
    if (b > 0) ans = ans * one;
    return ans.data[0];
}


int main() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    auto ans1 = rec(42);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "rec(42) = " << ans1 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans2 = iter(1200);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "iter(1200) = " << ans2 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    auto ans3 = gold(1200);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "gold(1200) = " << ans3 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
    auto ans4 = matr(1200);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "matr(1200) = " << ans4 << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count() << " ms)" << std::endl;
}