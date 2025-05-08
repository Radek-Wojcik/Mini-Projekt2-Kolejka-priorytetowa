#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    // Struktura przechowuj¹ca element, jego priorytet i kolejnoœæ wstawiania
    struct Node {
        T element;
        int priority;
        size_t insertionOrder;

        Node(const T& e, int p, size_t order) : element(e), priority(p), insertionOrder(order) {}
    };

    std::vector<Node> heap;
    size_t currentOrder; // Licznik do œledzenia kolejnoœci wstawiania
    std::mt19937 rng; // Generator liczb losowych
    int minPriority; // Minimalna wartoœæ priorytetu
    int maxPriority; // Maksymalna wartoœæ priorytetu

    // Metody pomocnicze dla operacji na kopcu
    void heapifyUp(int index);
    void heapifyDown(int index);
    int findElement(const T& element) const;
    int generateRandomPriority()

public:
    // Konstruktor z parametrami zakresu priorytetów
    PriorityQueue(int minPrio = 1, int maxPrio = 1000);

    void insert(const T& element, int priority = -1); // -1 to wygenerowanie losowego priorytetu
    T extractMax();
    T findMax() const;
    T peek() const;
    void modifyKey(const T& element, int newPriority);
    void increaseKey(const T& element, int newPriority);
    void decreaseKey(const T& element, int newPriority);
    size_t returnSize() const;

    
    bool isEmpty() const;
    void setPriorityRange(int minPrio, int maxPrio);

};

extern template class PriorityQueue<int>;
extern template class PriorityQueue<double>;
extern template class PriorityQueue<std::string>;

#endif // PRIORITY_QUEUE_H