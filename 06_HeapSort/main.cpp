#include <iostream>
#include <vector>
#include "heapSort.h"
#include <algorithm>
#include <iomanip>

//Распечатка вектора
template<typename dType>
std::ostream &operator<<(std::ostream &os, const std::vector<dType> &data) {
    os << "[";
    bool first = true;
    for (const dType &rec : data) {
        if (!first) {
            os << ",";
        }
        os << rec;
        first = false;
    }
    os << "]";
    return os;
}

int main() {
    std::vector<int> data {9,5,10,8,2,1,0,3,11,4,6,7};
    std::vector<int> data2(data);
    std::cout << "Original vector: " << data << std::endl;
    heapSort(data);
    std::cout << "Sorted vector: " << data << std::endl;
    if (!std::is_sorted(data.begin(), data.end())) {
        std::cout << "Incorrect sort" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Correct sort" << std::endl;
    }
    std::cout << "Original vector: " << data2 << std::endl;
    buildHeap(data2);
    std::cout << "Heap: " << data2 << std::endl;
    bool isCorrectHeap = checkHeap(data2);
    std::cout << "Is heap correct? " << std::boolalpha << isCorrectHeap << std::endl;
    std::cout << "Deleting 3rd element (8)" << std::endl;
    int deleted = heapDelete(data2, 3);
    std::cout << "Deleted " << deleted << std::endl;
    std::cout << "Heap: " << data2 << std::endl;
    isCorrectHeap = checkHeap(data2);
    std::cout << "Is heap correct? " << std::boolalpha << isCorrectHeap << std::endl;
    std::vector<int> data3{10, 2, 9, 1, 1, 8};
    std::cout << "New vector" << std::endl;
    isCorrectHeap = checkHeap(data3);
    std::cout << "Is heap correct? " << std::boolalpha << isCorrectHeap << std::endl;
    deleted = heapDelete(data3, 3);
    std::cout << "Deleted " << deleted << std::endl;
    std::cout << "Heap: " << data3 << std::endl;
    isCorrectHeap = checkHeap(data3);
    std::cout << "Is heap correct? " << std::boolalpha << isCorrectHeap << std::endl;
    return EXIT_SUCCESS;
}