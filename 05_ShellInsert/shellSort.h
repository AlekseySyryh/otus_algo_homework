#pragma once

#include "sequence.h"
#include <functional>

template<class array>
void shellSort(array &data, std::function<std::vector<size_t>(size_t)> seq) {
    for (size_t step: seq(data.size())) {
        for (size_t offset = 0; offset < step; ++offset) {
            insertSort(data, step, offset);
        }
    }
}