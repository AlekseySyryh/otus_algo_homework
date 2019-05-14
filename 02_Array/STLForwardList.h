#pragma once

#include <forward_list>
#include <iterator>
#include "IArray.h"

template<typename T>
class STLForwardList : public IArray<T> {
public:
    size_t size() const override {
        return std::distance(array.begin(), array.end());
    }

    void add(T item) override {
        if (array.empty()) {
            array.emplace_front(item);
        } else {
            auto it = array.begin();
            auto next = std::next(it);
            while (next != array.end()) {
                it = next++;
            }
            array.emplace_after(it, item);
        }
    }

    T get(size_t index) const override {
        return *(std::next(array.begin(), index));
    }

    void add(T item, size_t index) override {
        if (index == 0) {
            array.emplace_front(item);
        } else {
            array.emplace_after(std::next(array.begin(), index - 1), item);
        }
    }

    T remove(size_t index) override {
        T deleted;
        if (index == 0) {
            deleted = *array.begin();
            array.pop_front();
        } else {
            auto deleteAfter = std::next(array.begin(), index - 1);
            deleted = *std::next(deleteAfter);
            array.erase_after(deleteAfter);
        }
        return deleted;
    }

    void reset() override {
        array.clear();
    }

private:
    std::forward_list<T> array;
};