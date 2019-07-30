#include <iostream>
#include <vector>
#include "merge.h"
#include <algorithm>
#include <chrono>

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    size_t len = 10000000;
    std::vector<int> data(len);
    for (int i = 0; i < len; ++i) {
        data[i] = rand();
    }
    std::vector<int> data2(data);
    std::cout << "Classic ";
    start = std::chrono::system_clock::now();
    mergeSortClassic(data2);
    end = std::chrono::system_clock::now();
    if (std::is_sorted(data2.begin(), data2.end())) {
        std::cout << "OK (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)"
                  << std::endl;
    } else {
        std::cout << "Fail";
        return EXIT_FAILURE;
    }
    data2 = std::vector<int>(data);
    std::cout << "With insert ";
    start = std::chrono::system_clock::now();
    mergeSortInsert(data2);
    end = std::chrono::system_clock::now();
    if (std::is_sorted(data2.begin(), data2.end())) {
        std::cout << "OK (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)"
                  << std::endl;
    } else {
        std::cout << "Fail";
        return EXIT_FAILURE;
    }
    data2 = std::vector<int>(data);
    std::cout << "Parallel ";
    start = std::chrono::system_clock::now();
    mergeSortParallel(data2);
    end = std::chrono::system_clock::now();
    if (std::is_sorted(data2.begin(), data2.end())) {
        std::cout << "OK (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)"
                  << std::endl;
    } else {
        std::cout << "Fail";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}