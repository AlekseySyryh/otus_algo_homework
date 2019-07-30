#pragma once

#include <vector>
#include "heapSort.h"

template<typename T>
class PriorityRec {
public:
    int priority;
    T item;

    bool operator<(const PriorityRec<T> &other) {
        return priority < other.priority;
    }
};


template<typename T>
class PriorityQueue {
public:
    void enqueue(int priority, T item) {
        PriorityRec<T> newRec{priority, item};
        size_t i = recs.size();
        recs.push_back(newRec);
        while (i != 0) {
            i = parent(i);
            drown(recs, i, recs.size());
        }
    }

    T dequeue() {
        T value = recs[0].item;
        std::swap(recs[0], recs.back());
        recs.pop_back();
        drown(recs, 0, recs.size());
        return value;
    }

private:
    std::vector<PriorityRec<T>> recs;
};