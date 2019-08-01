#pragma once

#include <vector>

void insertSort(std::vector<int> &data, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        auto x = data.at(i);
        int j = i - 1;
        while (j >= begin && data.at(j) > x) {
            data.at(j + 1) = data.at(j);
            --j;
        }
        data.at(j + 1) = x;
    }
}