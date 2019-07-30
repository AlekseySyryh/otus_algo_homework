#pragma once

template<typename array>
void merge(array &data, array &copy, int begin, int mid, int end) {
    int first = begin;
    int second = mid;
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
void splitClassic(array &data, array &copy, int begin, int end) {
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

template<typename array>
void splitInsert(array &data, array &copy, int begin, int end) {
    if (end - begin < 16) {
        for (int i = begin; i < end; ++i) {
            auto x = data[i];
            int j = i - 1;
            while (j >= begin && data[j] > x) {
                data[j + 1] = data[j];
                copy[j + 1] = data[j];
                --j;
            }
            data[j + 1] = x;
            copy[j + 1] = x;
        }
        return;
    }

    auto mid = (end + begin) / 2;
    splitInsert(copy, data, begin, mid);
    splitInsert(copy, data, mid, end);
    merge(copy, data, begin, mid, end);
}

template<typename array>
void mergeSortInsert(array &data) {
    array copy(data);
    splitInsert(data, copy, 0, data.size());
}