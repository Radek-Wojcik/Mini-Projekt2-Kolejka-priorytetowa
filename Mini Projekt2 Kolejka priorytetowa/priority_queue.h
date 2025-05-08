#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    // Struktura przechowuj�ca element, jego priorytet i kolejno�� wstawiania
    struct Node {
        T element;
        int priority;
        size_t insertionOrder;

        Node(const T& e, int p, size_t order) : element(e), priority(p), insertionOrder(order) {}
    };

    std::vector<Node> heap;
    size_t currentOrder; // Licznik do �ledzenia kolejno�ci wstawiania
    std::mt19937 rng; // Generator liczb losowych
    int minPriority; // Minimalna warto�� priorytetu
    int maxPriority; // Maksymalna warto�� priorytetu

    // Metody pomocnicze dla operacji na kopcu
    void heapifyUp(int index);
    void heapifyDown(int index);
    int findElement(const T& element) const;
    int generateRandomPriority()

public:


};

#endif // PRIORITY_QUEUE_H