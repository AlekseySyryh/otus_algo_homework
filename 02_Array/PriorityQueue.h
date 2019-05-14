#pragma once

#include "VectorArray.h"
#include "DoubleLinkedList.h"

template<typename T>
struct PriorityRec {
    int Priority;
    DoubleLinkedList<T> recs;
};

template<typename T>
class PriorityQueue {
public:
    void enqueue(int priority, T item) {
        for (int i = 0; i < data.size(); ++i) {
            auto rec = data.get(i);
            if (rec->Priority == priority) {
                rec->recs.add(item);
                return;
            }
            if (rec->Priority < priority) {
                auto newRec = new PriorityRec<T>{priority};
                newRec->recs.add(item);
                data.add(newRec, i);
                return;
            }
        }
        auto newRec = new PriorityRec<T>{priority};
        newRec->recs.add(item);
        data.add(newRec);
    }

    T dequeue() {
        T rec = data.get(0)->recs.remove(0);
        if (data.get(0)->recs.size() == 0) {
            data.remove(0);
        }
        return rec;
    }

private:
    VectorArray<PriorityRec<T> *> data;
};