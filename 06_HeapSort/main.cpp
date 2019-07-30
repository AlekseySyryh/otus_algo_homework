#include <iostream>
#include <vector>
#include "heapSort.h"

int main() {
    std::vector<int> data {9,5,10,8,2,1,0,3,11,4,6,7};
    heapSort(data);
    return EXIT_SUCCESS;
}