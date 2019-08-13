#pragma once
#include <cmath>


size_t parent(size_t i){
    return std::floor((i - 1) / 2);
}

size_t leftChild(size_t i){
    return i * 2 + 1;
}

size_t rightChild(size_t i){
    return i * 2 + 2;
}

template <typename array>
void drown(array &heap, size_t i, size_t size) {
    size_t largest = i;
    do {
        i = largest;
        size_t l = leftChild(i);
        size_t r = rightChild(i);
        if (l < size && heap[i] < heap[l])
            largest = l;
        else
            largest = i;
        if (r < size && heap[largest] < heap[r])
            largest = r;
        if (largest != i)
            std::swap(heap[i], heap[largest]);
    } while (i != largest);
}

template <typename array>
void buildHeap(array &heap){
    size_t i = std::floor((heap.size() - 1) / 2) + 1;
    do {
        --i;
        drown(heap, i, heap.size());
    } while (i != 0);
}

template <typename array>
void heapSort(array &heap) {
    buildHeap(heap);
    size_t i = heap.size() - 1;
    do {
        std::swap(heap[0], heap[i]);
        drown(heap, 0, i);
        --i;
    } while (i != 0);
}

template<typename array>
bool checkHeap(const array &heap) {
    for (size_t i = 0; leftChild(i) < heap.size(); ++i) {
        if (heap[i] < heap[leftChild(i)] ||
                (rightChild(i) < heap.size() && heap[i] < heap[rightChild(i)]))
            return false;
    }
    return true;
}

template<typename dType>
dType heapDelete(std::vector<dType> &data, size_t ix) {
    std::swap(data[ix], data.back());
    dType deleted = data.back();
    data.pop_back();
    while (true) {
        drown(data, ix, data.size());
        if (ix == 0) break;
        ix = parent(ix);
    }
    return deleted;
}