#pragma once

template<class array>
void insertSort(array &data) {
    int n = data.size();
    for (int i = 0; i < n; ++i) {
        auto x = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > x) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = x;
    }
}

template<class array>
void insertSort(array &data, size_t step, size_t offset) {
    int n = data.size();
    for (int i = offset; i < n; i += step) {
        auto x = data[i];
        int j = i - step;
        while (j >= 0 && data[j] > x) {
            data[j + step] = data[j];
            j -= step;
        }
        data[j + step] = x;
    }
}