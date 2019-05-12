#pragma once

#include "IArray.h"

template <typename T>
struct Rec{
    T item;
    Rec* next = nullptr;
};

template <typename T>
class LinkedList:public IArray<T>{
public:
    LinkedList():size_(0),first(nullptr){}
    ~LinkedList(){
        reset();
    }

    size_t size() const override {
        return size_;
    }

    void add(T item) override {
        add(item,size_);
    }

    T get(size_t index) const override {
        return find(index)->item;
    }

    void add(T item, size_t index) override {
        Rec<T>* newRec = new Rec<T>;
        newRec->item = item;
        if (index == 0){
            newRec->next = first;
            first = newRec;
        } else {
            Rec<T>* prevRec = find(index-1);
            newRec->next = prevRec->next;
            prevRec->next = newRec;
        }
        ++size_;
    }

    T remove(size_t index) override {
        Rec<T>* rec;
        if (index == 0) {
            rec = first;
            first = rec->next;
        } else {
            Rec<T>* prevRec = find(index-1);
            rec = prevRec->next;
            prevRec->next = rec->next;
        }
        T deleted = rec->item;
        delete(rec);
        --size_;
        return deleted;
    }

    void reset() override {
        while (first != nullptr){
            auto next = first->next;
            delete(first);
            first = next;
        }
        size_ = 0;
    }
private:
    Rec<T>* find(size_t index) const{
        Rec<T>* rec = first;
        for (int i = 0; i < index; ++i) {
            rec = rec->next;
        }
        return rec;
    }
    size_t size_;

    Rec<T>* first;
};