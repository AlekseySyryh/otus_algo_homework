#pragma once

#include <list>
#include <utility>
#include "IArray.h"

template<typename T>
class STLList : public IArray<T> {
public:
    size_t size() const override {
        return array.size();
    }

    void add(T item) override {
        array.emplace_back(item);
    }

    T get(size_t index) const override {
        return *getIterator(index);
    }

    void add(T item, size_t index) override {
        if (index == 0) {
            array.emplace_front(item);
        } else if (index == array.size()) {
            array.emplace_back(item);
        } else {
            array.emplace(getIterator(index), item);
        }
    }

    T remove(size_t index) override {
        auto it = getIterator(index);
        T deleted = *it;
        array.erase(it);
        return deleted;
    }

    void reset() override {
        array.clear();
    }

private:
    auto getIterator(size_t index) const {
        if (index < size() / 2) {
            return std::next(array.begin(), index);
        } else {
            return std::prev(array.end(), size() - index);
        }
    }

    std::list<T> array;
};