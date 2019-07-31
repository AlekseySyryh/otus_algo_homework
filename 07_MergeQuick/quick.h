#pragma once

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

bool quickSortStep(std::vector<int> &data, int begin, int end, size_t level, pivotStrategy strategy) {
    if (level > maxLevel) return false;
    if (begin < end) {
        int pivot = partition(data, begin, end, strategy);
        if (!quickSortStep(data, begin, pivot, level + 1, strategy))
            return false;
        if (!quickSortStep(data, pivot + 1, end, level + 1, strategy))
            return false;
    }
    return true;
}

bool quickSort(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::last);
}

bool quickSortMedian(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::median);
}

bool quickSortRandom(std::vector<int> &data) {
    return quickSortStep(data, 0, data.size(), 0, pivotStrategy::random);
}

