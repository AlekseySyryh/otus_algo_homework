#pragma once

#include <future>
#include "insertSort.h"

enum pivotStrategy {
    last,
    median,
    random
};

int partition(std::vector<int> &data, int begin, int end, pivotStrategy strategy) {
    if (strategy == pivotStrategy::median) {
        int middleIx = (begin + end) / 2;
        int first = data[begin];
        int mid = data[middleIx];
        int last = data[end - 1];
        if ((first >= mid && first <= last) || (first <= mid && first >= last)) {
            std::swap(data[begin], data[end - 1]);
        } else if ((mid >= first && mid <= last) || (mid <= first && mid >= last)) {
            std::swap(data[middleIx], data[end - 1]);
        }
    } else if (strategy == pivotStrategy::random) {
        if (end - begin != 1) {
            int ix = begin + 1.0 * std::rand() * (end - begin - 1) / RAND_MAX;
            std::swap(data[ix], data[end - 1]);
        }
    }
    int pivot = data[end - 1];
    int i = begin - 1;
    for (int j = begin; j < end - 1; ++j) {
        if (data[j] <= pivot) {
            ++i;
            std::swap(data[i], data[j]);
        }
    }
    std::swap(data[i + 1], data[end - 1]);
    return i + 1;
}

static size_t maxLevel = 10000;

bool quickSortStep(std::vector<int> &data, int begin, int end, size_t level, pivotStrategy strategy, bool useInsert) {
    if (level > maxLevel) return false;
    if (begin >= end) return true;
    if (useInsert && end - begin < 32) {
        insertSort(data, begin, end);
        return true;
    }
        int pivot = partition(data, begin, end, strategy);
    if (!quickSortStep(data, begin, pivot, level + 1, strategy, useInsert))
            return false;
    if (!quickSortStep(data, pivot + 1, end, level + 1, strategy, useInsert))
            return false;

    return true;
}

bool quickSortParallelStep(std::vector<int> &data, int begin, int end, size_t level, pivotStrategy strategy,
                           bool useInsert) {
    if (level > maxLevel) return false;
    if (begin >= end) return true;
    if (useInsert && end - begin < 32) {
        insertSort(data, begin, end);
        return true;
    }
    int pivot = partition(data, begin, end, strategy);
    auto t1 = std::async(
            [=, &data]() { return quickSortParallelStep(data, begin, pivot, level + 1, strategy, useInsert); });
    auto t2 = std::async(
            [=, &data]() { return quickSortParallelStep(data, pivot + 1, end, level + 1, strategy, useInsert); });
    if (!t1.get() || !t2.get()) return false;
    return true;
}

bool quickSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::last, false);
}

bool quickMedianSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::median, false);
}

bool quickRandomSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::random, false);
}

bool quickInsertSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::last, true);
}

bool quickInsertMedianSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::median, true);
}

bool quickInsertRandomSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::random, true);
}

bool quickParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, 0, data.size(), 0, pivotStrategy::last, false);
}