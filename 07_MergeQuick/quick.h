#pragma once

int partition(std::vector<int> &data, int begin, int end) {
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

bool quickSortClassicStep(std::vector<int> &data, int begin, int end, size_t level) {
    if (level > maxLevel) return false;
    if (begin < end) {
        int pivot = partition(data, begin, end);
        if (!quickSortClassicStep(data, begin, pivot, level + 1))
            return false;
        if (!quickSortClassicStep(data, pivot + 1, end, level + 1))
            return false;
    }
    return true;
}

bool quickSortClassic(std::vector<int> &data) {
    return quickSortClassicStep(data, 0, data.size(), 0);
}