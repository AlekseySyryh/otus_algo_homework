#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include "IArray.h"

#define Test(array,n) std::cout << #array << std::endl; if (checkValid(array)) checkPerformance(array,n)

bool checkValid(IArray<int>& array){
    size_t s0 = array.size();
    array.add(1);
    size_t s1 = array.size();
    array.add(3);
    size_t s2 = array.size();
    array.add(2,1);
    size_t s3 = array.size();
    if (s0 == 0 && s1 == 1 && s2 == 2 && s3 == 3){
        std::cout << "Size - OK" << std::endl;
    } else  {
        std::cout << "Size - Fail" << std::endl;
        return false;
    }
    if (array.get(0) == 1 && array.get(1) == 2 && array.get(2) == 3) {
        std::cout << "Add/Get - OK" << std::endl;
    } else  {
        std::cout << "Add/Get - Fail" << std::endl;
        return false;
    }
    if (array.remove(1) == 2 && array.get(0) == 1 && array.get(1) == 3 && array.size() == 2 &&
        array.remove(1) == 3 && array.get(0) == 1 && array.size() == 1 &&
        array.remove(0) == 1 && array.size() == 0) {
        std::cout << "Remove - OK" << std::endl;
    } else  {
        std::cout << "Remove - Fail" << std::endl;
        return false;
    }
    return true;
}

void checkPerformance(IArray<int>& array, size_t n){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    array.reset();
    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < n; ++i) {
        array.add(i,0);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " inserts into first position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    array.reset();


    std::vector<size_t> ixes(n);
    for (size_t i = 0; i < n; ++i) {
        ixes[i] = std::rand()%(i+1); //вычисление rand внутри цикла - нежелательное замедление
    }
    start = std::chrono::system_clock::now();
    for (const auto& ix : ixes) {
        array.add(ix,ix);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " inserts into random position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    array.reset();

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < n; ++i) {
        array.add(i);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " inserts into last position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < n; ++i) {
        array.get(0);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " reads from first position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    for (size_t i = 0; i < n; ++i) {
        ixes[i] = std::rand()%(n+1);
    }
    start = std::chrono::system_clock::now();
    for (const auto& ix : ixes) {
        array.get(ix);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " reads from random position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    for (size_t i = 0; i < n; ++i) {
        array.get(n-1);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " reads from last position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    array.reset();
    for (size_t i = 0; i < n; ++i) {
        array.add(i,i);
    }
    start = std::chrono::system_clock::now();
    while (array.size() > 0) {
        array.remove(0);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " removes from first position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    array.reset();
    for (size_t i = 0; i < n; ++i) {
        array.add(i,i);
    } start = std::chrono::system_clock::now();
    while (array.size() > 0) {
        array.remove(array.size()-1);
    }
    end = std::chrono::system_clock::now();
    std::cout << n << " removes from last position " << std::chrono::duration_cast<std::chrono::milliseconds>
            (end-start).count() << "ms." << std::endl;
    array.reset();
}
