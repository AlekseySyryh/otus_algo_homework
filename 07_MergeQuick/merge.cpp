#include <iostream>
#include <vector>
#include "merge.h"
#include <algorithm>
#include <chrono>

void doTest(std::vector<int> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::vector<int> d(data);
    std::cout << "Classic ";
    start = std::chrono::high_resolution_clock::now();
    mergeSortClassic(d);
    end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(d.begin(), d.end())) {
        std::cout << "Fail!";
        exit(EXIT_FAILURE);
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    d = std::vector<int>(data);
    std::cout << "With insert ";
    start = std::chrono::high_resolution_clock::now();
    mergeSortInsert(d);
    end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(d.begin(), d.end())) {
        std::cout << "Fail!";
        exit(EXIT_FAILURE);
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    d = std::vector<int>(data);
    std::cout << "Parallel split ";
    start = std::chrono::high_resolution_clock::now();
    mergeSortParallel(d);
    end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(d.begin(), d.end())) {
        std::cout << "Fail!";
        exit(EXIT_FAILURE);
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    d = std::vector<int>(data);
    std::cout << "Run ";
    start = std::chrono::high_resolution_clock::now();
    mergeSortRun(d);
    end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(d.begin(), d.end())) {
        std::cout << "Fail!";
        exit(EXIT_FAILURE);
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    d = std::vector<int>(data);
    std::cout << "Run parallel merge ";
    start = std::chrono::high_resolution_clock::now();
    mergeSortRunParallel(d);
    end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(d.begin(), d.end())) {
        std::cout << "Fail!";
        exit(EXIT_FAILURE);
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

void test(int len) {
    std::cout << len << " Random" << std::endl;
    std::vector<int> data(len);
    for (int i = 0; i < len; ++i) {
        data[i] = rand();
    }
    doTest(data);
    std::sort(data.begin(), data.end());
    for (int i = 0; i < 5; ++i) {
        long ix1 = std::rand() / (RAND_MAX * len);
        long ix2 = std::rand() / (RAND_MAX * len);
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 5 elemets swaped" << std::endl;
    doTest(data);
    std::reverse(data.begin(), data.end());
    std::cout << len << " reversed" << std::endl;
    doTest(data);
    for (int i = 0; i < 5; ++i) {
        long ix1 = std::rand() / (RAND_MAX * len);
        long ix2 = std::rand() / (RAND_MAX * len);
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 5 elemets swaped  and reversed" << std::endl;
    doTest(data);
    std::sort(data.begin(), data.end());
    for (int i = 0; i < len * 0.1; ++i) {
        long ix1 = std::rand() / (RAND_MAX * len);
        long ix2 = std::rand() / (RAND_MAX * len);
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 10% elemets swaped" << std::endl;
    doTest(data);
    std::reverse(data.begin(), data.end());
    std::cout << len << " 10% elemets swaped and reversed" << std::endl;
    doTest(data);
}


int main() {
    int len = 10;
    while (len <= 10000000) {
        test(len);
        len *= 10;
    }
}