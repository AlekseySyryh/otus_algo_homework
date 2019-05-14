#include <iostream>
#include "PriorityQueue.h"

int main() {
    PriorityQueue<int> pq;
    pq.enqueue(0, 1000);
    pq.enqueue(1, 100);
    pq.enqueue(1, 101);
    if (pq.dequeue() != 100) {
        std::cerr << "Fail";
        return (EXIT_FAILURE);
    }
    pq.enqueue(-1, -1000);
    pq.enqueue(100, 1);
    if (pq.dequeue() != 1) {
        std::cerr << "Fail";
        return (EXIT_FAILURE);
    }
    if (pq.dequeue() != 101) {
        std::cerr << "Fail";
        return (EXIT_FAILURE);
    }
    if (pq.dequeue() != 1000) {
        std::cerr << "Fail";
        return (EXIT_FAILURE);
    }
    if (pq.dequeue() != -1000) {
        std::cerr << "Fail";
        return (EXIT_FAILURE);
    }
    std::cout << "OK";
    return (EXIT_SUCCESS);
}