#pragma once

template <typename T>
struct IArray {
    virtual size_t size() const = 0;
    virtual void add(T item) =0;
    virtual T get(size_t index) const =0;
    virtual void add(T item, size_t index) =0;
    virtual T remove(size_t index) =0;
    virtual void reset() = 0;
};