#include <iostream>
#include <vector>
#include "quick.h"
#include <algorithm>
#include <chrono>
#include <functional>
#include <string>
#include <unordered_map>

struct algInfo {
    std::string Name;
    std::function<bool(std::vector<int> &)> Func;
};

std::vector<algInfo> algorithms =
        {
                {"Classic",                            quickSort},
                {"Median pivot",                       quickMedianSort},
                {"Random pivot",                       quickRandomSort},
                {"Classic+Insert",                     quickInsertSort},
                {"Median+Insert",                      quickInsertMedianSort},
                {"Random+Insert",                      quickInsertRandomSort},
                {"Classic+Parallel",             quickParallelSort},
                {"Median+Parallel",              quickMedianParallelSort},
                {"Random+Parallel",              quickRandomParallelSort},
                {"Classic+Insert+Parallel",      quickInsertParallelSort},
                {"Median+Insert+Parallel",       quickInsertMedianParallelSort},
                {"Random+Insert+Parallel",       quickInsertRandomParallelSort},
                {"3way Classic",                 quick3WaySort},
                {"3way Median pivot",            quick3WayMedianSort},
                {"3way Random pivot",            quick3WayRandomSort},
                {"3way Classic+Insert",          quick3WayInsertSort},
                {"3way Median+Insert",           quick3WayInsertMedianSort},
                {"3way Random+Insert",                 quick3WayInsertRandomSort},
                {"3way Classic+Parallel",              quick3WayParallelSort},
                {"3way Median+Parallel",               quick3WayMedianParallelSort},
                {"3way Random+Parallel",               quick3WayRandomParallelSort},
                {"3way Classic+Insert+Parallel",       quick3WayInsertParallelSort},
                {"3way Median+Insert+Parallel",        quick3WayInsertMedianParallelSort},
                {"3way Random+Insert+Parallel",        quick3WayInsertRandomParallelSort},
                {"Intro",                              introSort},
                {"Intro Median pivot",                 introMedianSort},
                {"Intro Random pivot",                 introRandomSort},
                {"Intro Classic+Insert",               introInsertSort},
                {"Intro Median+Insert",                introInsertMedianSort},
                {"Intro Random+Insert",                introInsertRandomSort},
                {"Intro Classic+Parallel",             introParallelSort},
                {"Intro Median+Parallel",              introMedianParallelSort},
                {"Intro Random+Parallel",              introRandomParallelSort},
                {"Intro Classic+Insert+Parallel",      introInsertParallelSort},
                {"Intro Median+Insert+Parallel",       introInsertMedianParallelSort},
                {"Intro Random+Insert+Parallel",       introInsertRandomParallelSort},
                {"Intro 3way Classic",                 intro3WaySort},
                {"Intro 3way Median pivot",            intro3WayMedianSort},
                {"Intro 3way Random pivot",            intro3WayRandomSort},
                {"Intro 3way Classic+Insert",          intro3WayInsertSort},
                {"Intro 3way Median+Insert",           intro3WayInsertMedianSort},
                {"Intro 3way Random+Insert",           intro3WayInsertRandomSort},
                {"Intro 3way Classic+Parallel",        intro3WayParallelSort},
                {"Intro 3way Median+Parallel",         intro3WayMedianParallelSort},
                {"Intro 3way Random+Parallel",         intro3WayRandomParallelSort},
                {"Intro 3way Classic+Insert+Parallel", intro3WayInsertParallelSort},
                {"Intro 3way Median+Insert+Parallel",  intro3WayInsertMedianParallelSort},
                {"Intro 3way Random+Insert+Parallel",  intro3WayInsertRandomParallelSort}
        };

void doTest(std::vector<int> data, std::vector<algInfo> &algorithms) {
    std::vector<std::string> algsToRemove;
    for (const auto &alg : algorithms) {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        std::vector<int> d(data);
        std::cout << alg.Name << " ";
        start = std::chrono::high_resolution_clock::now();
        if (!alg.Func(d)) {
            std::cout << "stack overflow" << std::endl;
            algsToRemove.push_back(alg.Name);
            continue;
        }
        end = std::chrono::high_resolution_clock::now();
        if (!std::is_sorted(d.begin(), d.end())) {
            std::cout << "Fail!";
            exit(EXIT_FAILURE);
        }
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms"
                  << std::endl;
    }
    if (algsToRemove.size() > 0) {
        algorithms.erase(
                std::remove_if(algorithms.begin(), algorithms.end(), [&algsToRemove](const auto &alg) {
                    return std::count(algsToRemove.begin(), algsToRemove.end(), alg.Name) > 0;
                }), algorithms.end());
        algsToRemove.clear();
    }
}

std::unordered_map<int, std::vector<algInfo>> algsForTests;


void test(int len, std::vector<int> &data, int testAdd) {
    std::random_shuffle(data.begin(), data.end());
    doTest(data, algsForTests[testAdd]);
    std::sort(data.begin(), data.end());
    for (int i = 0; i < 5; ++i) {
        long ix1 = rand() % len;
        long ix2 = rand() % len;
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 5 elemets swaped" << std::endl;
    doTest(data, algsForTests[testAdd + 1]);
    std::reverse(data.begin(), data.end());
    std::cout << len << " 5 elemets swaped  and reversed" << std::endl;
    doTest(data, algsForTests[testAdd + 2]);
    std::sort(data.begin(), data.end());
    for (int i = 0; i < len * 0.1; ++i) {
        int ix1 = rand() % len;
        int ix2 = rand() % len;
        std::swap(data[ix1], data[ix2]);
    }
    std::cout << len << " 10% elemets swaped" << std::endl;
    doTest(data, algsForTests[testAdd + 3]);
    std::reverse(data.begin(), data.end());
    std::cout << len << " 10% elemets swaped and reversed" << std::endl;
    doTest(data, algsForTests[testAdd + 4]);
}

void test(int len) {
    std::cout << len << " Distinct Random" << std::endl;
    std::vector<int> data(len);
    for (int i = 0; i < len; ++i) {
        data[i] = i;
    }
    test(len, data, 0);
    std::cout << len << " 10% of diffirent values Random" << std::endl;
    for (int i = 0; i < len; ++i) {
        data[i] = i % (len / 10);
    }
    test(len, data, 5);
}

int main() {
    for (int i = 0; i < 10; ++i) {
        algsForTests[i] = std::vector<algInfo>(algorithms);
    }
    int len = 10;
    while (len <= 10000000) {
        test(len);
        len *= 10;
    }
}