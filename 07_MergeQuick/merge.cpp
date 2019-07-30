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
    std::cout << "Classic ";
    start = std::chrono::system_clock::now();
    mergeSortClassic(data);
    end = std::chrono::system_clock::now();
    if (std::is_sorted(data.begin(), data.end())) {
        std::cout << "OK (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << ") ms"
                  << std::endl;
    } else {
        std::cout << "Fail";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}