#pragma once

#include "IArray.h"
#include "LinkedList.h"
#include "VectorArray.h"


template <typename T>
struct FindResult {
    Rec<VectorArray<T>*>* block;
    size_t index;
};

template <typename T>
class SpaceArray: public IArray<T>{
public:
    SpaceArray():SpaceArray(10){}
    SpaceArray(size_t vector):vector(vector),size_(0){
        firstBlock = new Rec<VectorArray<T>*>;
        firstBlock->item = new VectorArray<T>(vector);
        lastBlock = firstBlock;
    }

    size_t size() const override {
        return size_;
    }

    void add(T item) override {
        if (lastBlock->item->size() == vector) {
            extendBlock(lastBlock);
        }
        lastBlock->item->add(item);
        ++size_;
    }

    T get(size_t index) const override {
        auto result = find(index);
        return result.block->item->get(result.index);
    }

    void add(T item, size_t index) override {
        auto result = find(index);
        auto insRec = result.block;
        if (insRec->item->size() == vector){
            extendBlock(insRec);
            result = find(index);
            insRec = result.block;
         }
        insRec->item->add(item, result.index);
        ++size_;
    }

    T remove(size_t index) override {
        auto result = find(index);
        T deleted = result.block->item->remove(result.index);
        if (result.block->item->size() == 0) {
            if (result.block != firstBlock) {
                auto *block = firstBlock;
                while (block->next != result.block) {
                    block = block->next;
                }
                block->next = result.block->next;
                delete (result.block);
                if (block->next == nullptr) {
                    lastBlock = block;
                }
            }
        }
        --size_;
        return deleted;
    }

    void reset() override {
        while (firstBlock != nullptr){
            auto block = firstBlock;
            firstBlock = firstBlock->next;
            delete(block->item);
            delete(block);
        }
        firstBlock = new Rec<VectorArray<T>*>;
        firstBlock->item = new VectorArray<T>(vector);
        lastBlock = firstBlock;
        size_ = 0;
    }

private:
    FindResult<T> find(size_t index) const {
        if (size_ - index < lastBlock->item->size()) {
            index -= (size_ - lastBlock->item->size());
            return {lastBlock, index};
        }
        auto *block = firstBlock;
        while (block->item->size() <= index &&
               block->next != nullptr){
            index -= (block->item->size());
            block = block->next;
        }
        return {block,index};
    }

    void extendBlock(Rec<VectorArray<T> *> *insRec) {
        auto newRec = new Rec<VectorArray<T> *>;
        newRec->item = new VectorArray<T>;
        newRec->next = insRec->next;
        insRec->next = newRec;
        for (int i = 0; i < vector / 2; ++i) {
            T itemToAdd = insRec->item->remove(insRec->item->size() - 1);
            newRec->item->add(itemToAdd, 0);
        }
        if (lastBlock->next != nullptr) {
            lastBlock = lastBlock->next;
        }
    }

    Rec<VectorArray<T> *> *firstBlock, *lastBlock;
    size_t size_;
    const size_t vector;
};