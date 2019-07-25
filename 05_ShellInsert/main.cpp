#include <iostream>
#include "insertsort.h"
#include <array>
#include <algorithm>

int main() {
    std::array<int, 5> data = {34, 24, 25, 53, 23};
    insertsort(data.begin(), data.end());
    std::for_each(data.begin(), data.end(), [](int x) { std::cout << x << " "; });
    return 0;
}