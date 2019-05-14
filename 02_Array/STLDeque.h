#pragma once

#include <deque>
#include "IArray.h"

template<typename T>
class STLDeque : public IArray<T> {
public:
    size_t size() const override {
        return array.size();
    }

    void add(T item) override {
        array.emplace_back(item);
    }

    T get(size_t index) const override {
        return array[index];
    }

    void add(T item, size_t index) override {
        array.emplace(array.begin() + index, item);
    }

    T remove(size_t index) override {
        T deleted = get(index);
        array.erase(array.begin() + index);
        return deleted;
    }

    void reset() override {
        array.clear();
    }

private:
    std::deque<T> array;
};