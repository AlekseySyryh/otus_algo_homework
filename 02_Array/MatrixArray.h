#pragma once

#include "IArray.h"
#include "SingleArray.h"
#include "VectorArray.h"

template <typename T>
class MatrixArray : public IArray<T>{
public:
    MatrixArray():MatrixArray(10){}
    MatrixArray(size_t vector):vector(vector),size_(0){
    }

    void reset() override {
        for (int i = 0; i < array.size(); ++i) {
            delete(array.get(i));
        }
        array.reset();
        size_ = 0;
    }

    size_t size() const override {
        return size_;
    }

    void add(T item) override {
        add(item, size_);
    }

    T get(size_t index) const override {
        return array.get(index / vector)->get(index % vector);
    }

    void add(T item, size_t index) override {
        if (size_ == array.size() * vector)
            array.add(new VectorArray<T>(vector));
        int binToInsert = index/vector;
        for (int i = array.size()-1;i > binToInsert; --i) {
            array.get(i)->add(array.get(i-1)->get(array.get(i-1)->size()-1),0);
            array.get(i-1)->remove(array.get(i-1)->size()-1);
        }
        array.get(binToInsert)->add(item,index%vector);
        ++size_;
    }

    T remove(size_t index) override {
        int binToRemove = index/vector;
        T removed = array.get(binToRemove)->remove(index%vector);
        for (int i = binToRemove+1; i < array.size(); ++i) {
            array.get(i-1)->add(array.get(i)->get(0));
            array.get(i)->remove(0);
        }
        if (array.get(array.size()-1)->size() == 0){
            //Формально не нужно, но так проще, + замена внешнего массива на VectorArray делает накладные расходы небольшими
            array.remove(array.size()-1);
        }
        --size_;
        return removed;
    }

private:
    VectorArray<VectorArray<T>*> array;
    size_t size_;
    const size_t vector;
};