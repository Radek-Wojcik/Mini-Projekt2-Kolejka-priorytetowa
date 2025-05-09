#include "heap_prio_queue.h"

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>


template <typename T>
HeapPrioQueue<T>::HeapPrioQueue(int minPrio, int maxPrio)
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
int HeapPrioQueue<T>::generateRandomPriority() {
    std::uniform_int_distribution<int> dist(minPriority, maxPriority);
    return dist(rng);
}

template <typename T>
void HeapPrioQueue<T>::setPriorityRange(int minPrio, int maxPrio) {
    if (minPrio < maxPrio) {
        minPriority = minPrio;
        maxPriority = maxPrio;
    }
}

template <typename T>
void HeapPrioQueue<T>::heapifyUp(int index) {
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
void HeapPrioQueue<T>::heapifyDown(int index) {
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
int HeapPrioQueue<T>::findElement(const T& element) const {
    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i].element == element) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void HeapPrioQueue<T>::insert(const T& element, int priority) {
    // Jeœli priorytet jest -1, wygeneruj losowy priorytet
    if (priority == -1) {
        priority = generateRandomPriority();
    }

    heap.push_back(Node(element, priority, currentOrder++));
    heapifyUp(heap.size() - 1);
}

template <typename T>
T HeapPrioQueue<T>::extractMax() {
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
T HeapPrioQueue<T>::findMax() const {
    if (isEmpty()) {
        throw std::runtime_error("Priority queue is empty");
    }

    return heap[0].element;
}

template <typename T>
T HeapPrioQueue<T>::peek() const {
    return findMax();
}

template <typename T>
void HeapPrioQueue<T>::modifyKey(const T& element, int newPriority) {
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

template <typename T>
void HeapPrioQueue<T>::increaseKey(const T& element, int newPriority) {
    int index = findElement(element);

    if (index == -1) {
        throw std::runtime_error("Element not found in the priority queue");
    }

    if (newPriority <= heap[index].priority) {
        throw std::runtime_error("New priority must be greater than current priority");
    }

    heap[index].priority = newPriority;
    heapifyUp(index);
}

template <typename T>
void HeapPrioQueue<T>::decreaseKey(const T& element, int newPriority) {
    int index = findElement(element);

    if (index == -1) {
        throw std::runtime_error("Element not found in the priority queue");
    }

    if (newPriority >= heap[index].priority) {
        throw std::runtime_error("New priority must be less than current priority");
    }

    heap[index].priority = newPriority;
    heapifyDown(index);
}

template <typename T>
size_t HeapPrioQueue<T>::returnSize() const {
    return heap.size();
}

template <typename T>
bool HeapPrioQueue<T>::isEmpty() const {
    return heap.empty();
}

template <typename T>
bool HeapPrioQueue<T>::find(const T& element) const {
    return findElement(element) != -1;
}

template <typename T>
bool HeapPrioQueue<T>::remove(const T& element) {
    int index = findElement(element);
    if (index == -1) {
        return false; // Element nie znaleziony
    }

    // Zamieñ element do usuniêcia z ostatnim elementem
    heap[index] = heap.back();
    heap.pop_back();

    // Jeœli usuniêty element nie by³ ostatnim, przywróæ w³aœciwoœci kopca
    if (index < static_cast<int>(heap.size())) {
        // SprawdŸ, czy trzeba przesun¹æ w górê czy w dó³
        int parent = (index - 1) / 2;
        if (index > 0 && (heap[parent].priority < heap[index].priority ||
            (heap[parent].priority == heap[index].priority &&
                heap[parent].insertionOrder > heap[index].insertionOrder))) {
            heapifyUp(index);
        }
        else {
            heapifyDown(index);
        }
    }

    return true;
}

template <typename T>
void HeapPrioQueue<T>::buildFromFile(const std::string& filename) {
    // Najpierw usuñ poprzednie dane
    clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        T element;
        int priority;

        // Zak³adamy, ¿e ka¿da linia zawiera element i priorytet oddzielone spacj¹
        if (iss >> element >> priority) {
            insert(element, priority);
        }
    }

    file.close();
}

template <typename T>
void HeapPrioQueue<T>::createRandom(size_t size) {
    // Wyczyœæ istniej¹ce dane
    clear();

    // Generuj losowe elementy i priorytety
    for (size_t i = 0; i < size; ++i) {
        // Dla typów liczbowych generujemy losowe wartoœci
        if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
            std::uniform_real_distribution<double> elemDist(1.0, 1000.0);
            T randomElement;

            if constexpr (std::is_same_v<T, int>) {
                randomElement = static_cast<int>(elemDist(rng));
            }
            else {
                randomElement = elemDist(rng);
            }

            insert(randomElement, generateRandomPriority());
        }
        // Dla stringów generujemy losowe ci¹gi znaków
        else if constexpr (std::is_same_v<T, std::string>) {
            std::string randomStr = "item_" + std::to_string(i);
            insert(randomStr, generateRandomPriority());
        }
        // Dla innych typów (jeœli bêd¹ u¿ywane) - domyœlna implementacja
        else {
            throw std::runtime_error("Random generation not supported for this type");
        }
    }
}

template class HeapPrioQueue<int>;
template class HeapPrioQueue<double>;
template class HeapPrioQueue<std::string>;
