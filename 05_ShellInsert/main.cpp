#include <iostream>
#include "insertsort.h"
#include "shellSort.h"
#include <array>
#include <algorithm>
#include <cstdlib>
#include <chrono>

void doTest(std::vector<int> data) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::vector<int> d1(data);
    std::cout << "Insert sort ";
    start = std::chrono::high_resolution_clock::now();
    insertSort(d1);
    end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(d1.begin(), d1.end())) {
        std::cout << "Fail!";
        exit(EXIT_FAILURE);
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    sequences allSequences;
    for (auto &seq : allSequences) {
        std::vector<int> d2(data);
        std::cout << "Shell sort (" << seq->GetName() << ") ";
        start = std::chrono::high_resolution_clock::now();
        shellSort(d2, [&seq](size_t len) { return seq->GetSeq(len); });
        end = std::chrono::high_resolution_clock::now();
        if (!std::is_sorted(d1.begin(), d1.end())) {
            std::cout << "Fail!";
            exit(EXIT_FAILURE);
        }
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    }
}

void test(size_t len) {
    std::cout << len << " Random" << std::endl;
    std::vector<int> data(len);
    for (int i = 0; i < len; ++i) {
        data[i] = rand();
    }

    std::sort(data.begin(), data.end());
    for (int i = 0; i < 5; ++i) {
        size_t ix1 = std::rand() * len / RAND_MAX;
        size_t ix2 = std::rand() * len / RAND_MAX;
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 5 elemets swaped" << std::endl;

    for (int i = 0; i < len * 0.1; ++i) {
        size_t ix1 = std::rand() * len / RAND_MAX;
        size_t ix2 = std::rand() * len / RAND_MAX;
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 10% elemets swaped" << std::endl;
}

int main() {
    int len = 20;
    while (len < 500000) {
        test(len);
        len *= 2;
    }
    return EXIT_SUCCESS;
}

