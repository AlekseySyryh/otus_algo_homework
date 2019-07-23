#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>

//3a. Через перебор делителей.
int enumerate(int n) {
    int a = 1;
    for (int i = 2; i <= n; ++i) {
        int div = 1;
        for (int j = 2; j <= i; ++j) {
            if (i % j == 0) {
                ++div;
            }
        }
        if (div == 2)++a;
    }
    return a;
}

//3b. Оптимизация перебора делителей.
int opt(int n) {
    int a = 2;
    for (int i = 3; i <= n; i += 2) {
        int div = 0;
        for (int j = 3; j <= std::sqrt(i); j += 2) {
            if (i % j == 0) {
                ++div;
                break;
            }
        }
        if (div == 0)++a;
    }
    return a;
}

//3c. Решето Эратосфена.
int erat(int n) {
    std::vector<int> nums(n, {1});//Если сделать std::vector<bool>, то неявно будет битовая матрица...
    int ix = 1;
    while (ix < n) {
        if (nums[ix] != 0) {
            int ix2 = ix * 2 + 1;
            while (ix2 < n) {
                nums[ix2] = 0;
                ix2 += (ix + 1);
            }
        }
        ++ix;
    }
    return std::count(nums.begin(), nums.end(), 1);
}

//3d. Решето Эратосфена с битовой матрицей, по 32 значения в одном int (по желанию)
int erat_bit(int n) {
    int bits = n / 32 + 1;
    std::vector<unsigned int> nums(bits, {0xFFFFFFFF});
    int ix = 1;
    while (ix < n) {
        int num = ix / 32;
        int off = ix % 32;
        int mask = 1 << off;
        if ((nums[num] & mask) != 0) {
            int ix2 = ix * 2 + 1;
            while (ix2 < n) {
                int num2 = ix2 / 32;
                int off2 = ix2 % 32;
                int mask2 = ~(1 << off2);
                nums[num2] &= mask2;
                ix2 += (ix + 1);
            }
        }
        ++ix;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int num = i / 32;
        int off = i % 32;
        int mask = 1 << off;
        if ((nums[num] & mask) != 0) ++ans;
    }
    return ans;
}

int main() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    auto ans1 = enumerate(100000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "enumerate(100000) = " << ans1 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    auto ans2 = opt(100000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "opt(100000) = " << ans2 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto ans3 = erat(100000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "erat(100000) = " << ans3 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto ans4 = erat_bit(100000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "erat_bit(100000) = " << ans4 << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count() << " ms)" << std::endl;


}