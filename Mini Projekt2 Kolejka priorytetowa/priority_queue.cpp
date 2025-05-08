#include "priority_queue.h"

#include <iostream>
#include <string>
#include <limits>

template <typename T>
PriorityQueue<T>::PriorityQueue(int minPrio, int maxPrio)
    : currentOrder(0),
    rng(static_cast<unsigned int>(std::time(nullptr))),
    minPriority(minPrio),
    maxPriority(maxPrio) {
    // Sprawdzenie, ¿e maxPriority jest wiêksze ni¿ minPriority
    if (minPriority >= maxPriority) {
        maxPriority = minPriority + 1000;     
    }
}

template <typename T>
int PriorityQueue<T>::generateRandomPriority() {
    std::uniform_int_distribution<int> dist(minPriority, maxPriority);
    return dist(rng);
}

template <typename T>
void PriorityQueue<T>::setPriorityRange(int minPrio, int maxPrio) {
    if (minPrio < maxPrio) {
        minPriority = minPrio;
        maxPriority = maxPrio;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    int parent = (index - 1) / 2;

    while (index > 0) {
        if (heap[parent].priority < heap[index].priority ||
            (heap[parent].priority == heap[index].priority &&
                heap[parent].insertionOrder > heap[index].insertionOrder)) {
            std::swap(heap[parent], heap[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
        else {
            break;
        }
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    int size = heap.size();

    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int highestPriorityIndex = index;

        if (leftChild < size &&
            (heap[leftChild].priority > heap[highestPriorityIndex].priority ||
                (heap[leftChild].priority == heap[highestPriorityIndex].priority &&
                    heap[leftChild].insertionOrder < heap[highestPriorityIndex].insertionOrder))) {
            highestPriorityIndex = leftChild;
        }

        if (rightChild < size &&
            (heap[rightChild].priority > heap[highestPriorityIndex].priority ||
                (heap[rightChild].priority == heap[highestPriorityIndex].priority &&
                    heap[rightChild].insertionOrder < heap[highestPriorityIndex].insertionOrder))) {
            highestPriorityIndex = rightChild;
        }

        if (highestPriorityIndex == index) {
            break;
        }

        std::swap(heap[index], heap[highestPriorityIndex]);
        index = highestPriorityIndex;
    }
}

template <typename T>
int PriorityQueue<T>::findElement(const T& element) const {
    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i].element == element) {
            return i;
        }
    }
    return -1;
}
