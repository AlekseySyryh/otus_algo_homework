#pragma once

#include "IArray.h"

template <typename T>
class SingleArray : public IArray<T>{
public:
    SingleArray():allocated(0) {
        array = new T[0];
    }
    ~SingleArray(){
        delete[](array);
    }
    void reset() {
        delete[](array);
        array = new T[0];
        allocated = 0;
    }

    size_t size()  const override {
        return allocated;
    }

    void add(T item) override {
        add(item, allocated);
    }

    T get(size_t index) const override {
        return array[index];
    }

    void add(T item, size_t index) override {
        T* newArray = new T[allocated+1];
        std::move(array, array+index, newArray);
        newArray[index] = item;
        std::move(array+index, array+allocated, newArray+index+1);
        delete[](array);
        array = newArray;
        ++allocated;
    }

    T remove(size_t index) override {
        T removed = array[index];
        T* newArray = new T[allocated-1];
        std::move(array, array+index, newArray);
        std::move(array+index+1, array+allocated, newArray+index);
        delete[](array);
        array = newArray;
        --allocated;
        return removed;
    }
private:
    T* array;
    size_t allocated;
};