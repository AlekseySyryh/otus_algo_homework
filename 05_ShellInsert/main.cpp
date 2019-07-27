#include <iostream>
#include "insertsort.h"
#include "shellSort.h"
#include <array>
#include <algorithm>

int main() {
    /*std::array<int, 5> data = {34, 24, 25, 53, 23};
    insertSort(data.begin(), data.end());
    std::for_each(data.begin(), data.end(), [](int x) { std::cout << x << " "; });*/
    sequences allSequences;
    for (auto &seq : allSequences) {
        std::cout << seq->GetName() << std::endl;
        for (auto offset : seq->GetSeq(1000)) {
            std::cout << offset << std::endl;
        }
    }
    return 0;
}

