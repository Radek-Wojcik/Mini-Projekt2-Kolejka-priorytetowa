#ifndef HEAP_PRIO_QUEUE_H
#define HEAP_PRIO_QUEUE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <ctime>

template <typename T>
class HeapPrioQueue {
private:
    // Struktura przechowuj¹ca element, jego priorytet i kolejnoœæ wstawiania
    struct Node {
        T element;                  // Wartoœæ przechowywanego elementu
        int priority;               // Priorytet elementu
        size_t insertionOrder;      // Kolejnoœæ wstawiania

        Node(const T& e, int p, size_t order) : element(e), priority(p), insertionOrder(order) {}   // Konstruktor wêz³a
    };

    std::vector<Node> heap;                     // Przechowywanie kopca jako tablica
    size_t currentOrder;                        // Licznik do œledzenia kolejnoœci wstawiania
    int minPriority;                            // Minimalna wartoœæ priorytetu
    int maxPriority;                            // Maksymalna wartoœæ priorytetu

    // Metody pomocnicze dla operacji na kopcu
    void heapifyUp(int index);                  // Przesuwa wêze³ o indeksie "index" w górê, aby przywróciæ w³asnoœæ kopca
    void heapifyDown(int index);                // Przesuwa wêze³ o indeksie "index" w dó³, aby przywróciæ w³asnoœæ kopca
    int findElement(const T& element) const;    // Znajduje indeks wêz³a zawieraj¹cego podany element lub -1, jeœli nie istnieje    

public:
    // Konstruktor z parametrami zakresu priorytetów
    HeapPrioQueue(int minPrio = 1, int maxPrio = 1000);

    void insert(const T& element, int priority);            // Wstawia element z okreœlonym priorytetem
    T extractMax();                                         // Usuwa i zwraca element o najwy¿szym priorytecie
    T findMax() const;                                      // Zwraca element o najwy¿szym priorytecie bez usuwania
    T peek() const;
    void modifyKey(const T& element, int newPriority);      // Modyfikuje priorytet podanego elementu
    void increaseKey(const T& element, int newPriority);    // Zwiêksza priorytet danego elementu
    void decreaseKey(const T& element, int newPriority);    // Zmniejsza priorytet danego elementu
    size_t returnSize() const;                              // Zwraca liczbê elementów w kolejce

    
    bool isEmpty() const;                                   // Sprawdza, czy kolejka jest pusta
    void setPriorityRange(int minPrio, int maxPrio);        // Ustawia nowy zakres mo¿liwych priorytetów

    bool find(const T& element) const;                      // metoda do znajdowania elementu
    bool remove(const T& element);                          // Usuniêcie konkretnego elementu
    void buildFromFile(const std::string& filename);        // Budowanie z pliku
    void createRandom(size_t size);                         // Tworzenie losowej struktury
    void display() const;                                   // Wyœwietlanie zawartoœci kolejki
    void clear();                                           // Czyszczenie kolejki

};

// Wymuszenie instancjacji szablonu
extern template class HeapPrioQueue<int>;
extern template class HeapPrioQueue<double>;
extern template class HeapPrioQueue<std::string>;

#endif // HEAP_PRIO_QUEUE_H