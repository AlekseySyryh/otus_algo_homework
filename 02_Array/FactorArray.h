#pragma once

#include "IArray.h"
template <typename T>
class FactorArray : public IArray<T> {
public:
    FactorArray():FactorArray(50,10){}
    FactorArray(size_t factor, size_t initLength):
        allocated(initLength), factor(factor),size_(0),initLength(initLength) {
        array = new T[allocated];
    }
    ~FactorArray(){
        delete[](array);
    }

    void reset() override {
        delete[](array);
        allocated = initLength;
        size_ = 0;
        array = new T[allocated];
    }

    size_t size() const override {
        return size_;
    }

    void add(T item) override {
        add(item, size_);
    }

    T get(size_t index) const override {
        return array[index];
    }


    void add(T item, size_t index) override {
        if (size_ == allocated) {
            resize();
        }
        std::move_backward(array + index, array + size_, array + size_ + 1);
        array[index]=item;
        ++size_;
    }

    T remove(size_t index) override {
        T removed = array[index];
        std::move(array + index + 1, array + size_, array + index);
        --size_;
        return removed;
    }

private:
    void resize(){
        T* newArray = new T[allocated+allocated*factor/100];
        std::move(array,array+allocated,newArray);
        delete[](array);
        array = newArray;
        allocated += allocated*factor/100;
    }
    T* array;
    const size_t initLength,factor;
    size_t allocated,size_;
};