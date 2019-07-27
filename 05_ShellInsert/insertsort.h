#pragma once

//По рабоче-крестьянски
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



//Модно, стильно, молодежно, по STLному (у нас тут современный C++ или где?)
template<class BidirectionalIt, class Compare>
void insertSort(BidirectionalIt first, BidirectionalIt last, Compare comp) {
    if (first == last) return;
    for (auto it = std::next(first); it < last; ++it) {
        auto x = *it;
        auto j = std::prev(it);
        bool moveNeeded = true;
        while (comp(x, *j)) {
            *std::next(j) = *j;
            if (j == first) { //Пришлось чутка покостылить, ведь std::prev(first) - это UB.
                moveNeeded = false;
                *j = x;
                break;
            }
            --j;
        }
        if (moveNeeded) {
            *std::next(j) = x;
        }
    }
}

template<class BidirectionalIt>
void insertSort(BidirectionalIt first, BidirectionalIt last) {
    insertSort(first, last, std::less<>());
}