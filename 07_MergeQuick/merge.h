#pragma once

template<typename array>
void merge(array &data, array &copy, size_t begin, size_t mid, size_t end) {
    size_t first = begin;
    size_t second = mid;
    for (size_t ptr = begin; ptr < end; ++ptr) {
        if (first < mid && (second == end || data[first] < data[second])) {
            copy[ptr] = data[first];
            ++first;
        } else {
            copy[ptr] = data[second];
            ++second;
        }
    }
}

template<typename array>
void splitClassic(array &data, array &copy, size_t begin, size_t end) {
    if (end - begin < 2)
        return;
    auto mid = (end + begin) / 2;
    splitClassic(copy, data, begin, mid);
    splitClassic(copy, data, mid, end);
    merge(copy, data, begin, mid, end);
}

template<typename array>
void mergeSortClassic(array &data) {
    array copy(data);
    splitClassic(data, copy, 0, data.size());
}