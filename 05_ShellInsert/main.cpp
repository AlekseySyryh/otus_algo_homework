#include <iostream>
#include "insertsort.h"
#include "shellSort.h"
#include <array>
#include <algorithm>

int main() {
    /*std::array<int, 5> data = {34, 24, 25, 53, 23};
    insertSort(data.begin(), data.end());
    */
    sequences allSequences;
    for (auto &seq : allSequences) {
        std::array<int, 8> data = {34, 24, 25, 53, 23, 36, 12, 35};
        std::cout << seq->GetName() << std::endl;
        shellSort(data, [&seq](size_t len) { return seq->GetSeq(len); });
        std::for_each(data.begin(), data.end(), [](int x) { std::cout << x << " "; });
        std::cout << std::endl;
    }
    return 0;
}

