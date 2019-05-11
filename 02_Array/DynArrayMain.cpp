#include <iostream>
#include <chrono>
#include <vector> //это не криминал - это только для замера быстродействия.

#include "SingleArray.h"
#include "IArray.h"

#define CHECK(Variable,n) if (checkValid(#Variable,Variable)) checkPerformance(#Variable,Variable,n)

bool checkValid(std::string name, IArray<int>& array){
    size_t s0 = array.size();
    array.add(1);
    size_t s1 = array.size();
    array.add(3);
    size_t s2 = array.size();
    array.add(2,1);
    size_t s3 = array.size();
    if (s0 == 0 && s1 == 1 && s2 == 2 && s3 == 3){
        std::cout << name << ": Size - OK" << std::endl;
    } else  {
        std::cout << name << ": Size - Fail" << std::endl;
        return false;
    }
    if (array.get(0) == 1 && array.get(1) == 2 && array.get(2) == 3) {
        std::cout << name << ": Add/Get - OK" << std::endl;
    } else  {
        std::cout << name << ": Add/Get - Fail" << std::endl;
        return false;
    }
    if (array.remove(1) == 2 && array.get(0) == 1 && array.get(1) == 3 && array.size() == 2 &&
        array.remove(1) == 3 && array.get(0) == 1 && array.size() == 1 &&
        array.remove(0) == 1 && array.size() == 0) {
        std::cout << name << ": Remove - OK" << std::endl;
    } else  {
        std::cout << name << ": Remove - Fail" << std::endl;
        return false;
    }
    return true;
}

void checkPerformance(std::string name, IArray<int>& array, size_t n){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    //warmup...
    for (size_t i = 0; i < n; ++i) {
        array.add(i);
    }
    while (array.size() != 0){
        array.remove(0);
    }

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < n; ++i) {
        array.add(i,0);
    }
    end = std::chrono::system_clock::now();
    std::cout << name << ": " << n << " inserts into first position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    while (array.size() != 0){
        array.remove(0);
    }

    std::vector<size_t> ixes(n);
    for (size_t i = 0; i < n; ++i) {
        ixes[i] = std::rand()%(i+1); //вычисление rand внутри цикла - нежелательное замедление
    }
    start = std::chrono::system_clock::now();
    for (const auto& ix : ixes) {
        array.add(ix,ix);
    }
    end = std::chrono::system_clock::now();
    std::cout << name << ": " << n << " inserts into random position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    while (array.size() != 0){
        array.remove(0);
    }

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < n; ++i) {
        array.add(i);
    }
    end = std::chrono::system_clock::now();
    std::cout << name << ": " << n << " inserts into last position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < n; ++i) {
        array.get(0);
    }
    end = std::chrono::system_clock::now();
    std::cout << name << ": " << n << " reads from first position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    for (size_t i = 0; i < n; ++i) {
        ixes[i] = std::rand()%(n+1);
    }
    start = std::chrono::system_clock::now();
    for (const auto& ix : ixes) {
        array.get(ix);
    }
    end = std::chrono::system_clock::now();
    std::cout << name << ": " << n << " reads from random position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    for (size_t i = 0; i < n; ++i) {
        array.get(n-1);
    }
    end = std::chrono::system_clock::now();
    std::cout << name << ": " << n << " reads from last position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    while (array.size() != 0){
        array.remove(0);
    }
}

int main() {
    SingleArray<int> singleArray;
    CHECK(singleArray, 100000);
    return 0;
}