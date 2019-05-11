#pragma once

#include "IArray.h"

template <typename T>
class VectorArray : public IArray<T>{
public:
    VectorArray():VectorArray(10){

    }
    VectorArray(size_t vector):vector(vector){
        array = new T[0];
        allocated = 0;
        size_ = 0;
    }
    void reset() {
        delete[](array);
        array = new T[0];
        allocated = 0;
        size_ = 0;
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
        //Формально про освобождение памяти у нас требования нет.
        std::move(array + index + 1, array + size_, array + index);
        --size_;
        return removed;
    }

private:
    void resize(){
        T* newArray = new T[allocated+vector];
        std::copy(array,array+allocated,newArray);
        delete[](array);
        array = newArray;
        allocated += vector;
    }
    T* array;
    size_t allocated,vector,size_;
};