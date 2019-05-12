#pragma once

#include "IArray.h"

template <typename T>
struct DRec {
    T item;
    DRec *next = nullptr,*prev = nullptr;
};

template <typename T>
class DoubleLinkedList : public IArray<T> {
public:
    DoubleLinkedList():size_(0){}
    ~DoubleLinkedList(){
        reset();
    }

    size_t size() const override {
        return size_;
    }

    void add(T item) override {
        add(item, size_);
    }

    T get(size_t index) const override {
        return find(index)->item;
    }

    void add(T item, size_t index) override {
        DRec<T>* newRec = new DRec<T>;
        newRec->item = item;
        if (size_  == 0) {
            first = newRec;
            last = newRec;
        } else if (index == 0) {
            newRec -> next = first;
            first->prev = newRec;
            first = newRec;
        } else if (index == size_) {
            newRec -> prev = last;
            last->next = newRec;
            last = newRec;
        } else {
            DRec<T>* exist = find(index);
            exist->prev->next = newRec;
            newRec->prev = exist->prev;
            newRec->next = exist;
            exist->prev = newRec;
        }
        ++size_;
    }

    T remove(size_t index) override {
        DRec<T>* rec = find(index);
        if (size_==1){
            first = nullptr;
            last = nullptr;
        } else if (rec->prev == nullptr) {//first;
            first = rec->next;
            first->prev = rec->prev;
        } else if (rec->next == nullptr) {//last
            last = rec->prev;
            last->next = rec->next;
        } else {
            rec->prev->next = rec->next;
            rec->next->prev = rec->prev;
        }
        --size_;
        T deleted = rec->item;
        delete(rec);
        return deleted;
    }

    void reset() override {
        size_ = 0;
        last = nullptr;
        while (first != nullptr) {
            DRec<T>* rec = first;
            first = rec->next;
            delete(rec);
        }
    }

private:
    DRec<T>* find(size_t index) const {
        DRec<T> *rec;
        size_t ix;
        if (index > size_/2){
            rec = last;
            ix = size_-1;
            while (ix != index){
                --ix;
                rec = rec->prev;
            }
        } else {
            rec = first;
            ix = 0;
            while (ix != index){
                ++ix;
                rec = rec->next;
            }
        }
        return rec;
    }
    DRec<T> *first,*last;
    size_t size_;
};