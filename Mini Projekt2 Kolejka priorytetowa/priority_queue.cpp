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

template <typename T>
void PriorityQueue<T>::insert(const T& element, int priority) {
    // Jeœli priorytet jest -1, wygeneruj losowy priorytet
    if (priority == -1) {
        priority = generateRandomPriority();
    }

    heap.push_back(Node(element, priority, currentOrder++));
    heapifyUp(heap.size() - 1);
}

template <typename T>
T PriorityQueue<T>::extractMax() {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }

    T maxElement = heap[0].element;
    heap[0] = heap.back();
    heap.pop_back();

    if (!isEmpty()) {
        heapifyDown(0);
    }

    return maxElement;
}

template <typename T>
T PriorityQueue<T>::findMax() const {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }

    return heap[0].element;
}

template <typename T>
T PriorityQueue<T>::peek() const {
    return findMax();
}

template <typename T>
void PriorityQueue<T>::modifyKey(const T& element, int newPriority) {
    int index = findElement(element);

    if (index == -1) {
        throw std::runtime_error("Element not found in the priority queue");
    }

    int oldPriority = heap[index].priority;
    heap[index].priority = newPriority;

    if (newPriority > oldPriority) {
        heapifyUp(index);
    }
    else if (newPriority < oldPriority) {
        heapifyDown(index);
    }
}
