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
    // Struktura przechowuj�ca element, jego priorytet i kolejno�� wstawiania
    struct Node {
        T element;                  // Warto�� przechowywanego elementu
        int priority;               // Priorytet elementu
        size_t insertionOrder;      // Kolejno�� wstawiania

        Node(const T& e, int p, size_t order) : element(e), priority(p), insertionOrder(order) {}   // Konstruktor w�z�a
    };

    std::vector<Node> heap;                     // Przechowywanie kopca jako tablica
    size_t currentOrder;                        // Licznik do �ledzenia kolejno�ci wstawiania
    int minPriority;                            // Minimalna warto�� priorytetu
    int maxPriority;                            // Maksymalna warto�� priorytetu

    // Metody pomocnicze dla operacji na kopcu
    void heapifyUp(int index);                  // Przesuwa w�ze� o indeksie "index" w g�r�, aby przywr�ci� w�asno�� kopca
    void heapifyDown(int index);                // Przesuwa w�ze� o indeksie "index" w d�, aby przywr�ci� w�asno�� kopca
    int findElement(const T& element) const;    // Znajduje indeks w�z�a zawieraj�cego podany element lub -1, je�li nie istnieje    

public:
    // Konstruktor z parametrami zakresu priorytet�w
    HeapPrioQueue(int minPrio = 1, int maxPrio = 1000);

    void insert(const T& element, int priority);            // Wstawia element z okre�lonym priorytetem
    T extractMax();                                         // Usuwa i zwraca element o najwy�szym priorytecie
    T findMax() const;                                      // Zwraca element o najwy�szym priorytecie bez usuwania
    T peek() const;
    void modifyKey(const T& element, int newPriority);      // Modyfikuje priorytet podanego elementu
    void increaseKey(const T& element, int newPriority);    // Zwi�ksza priorytet danego elementu
    void decreaseKey(const T& element, int newPriority);    // Zmniejsza priorytet danego elementu
    size_t returnSize() const;                              // Zwraca liczb� element�w w kolejce

    
    bool isEmpty() const;                                   // Sprawdza, czy kolejka jest pusta
    void setPriorityRange(int minPrio, int maxPrio);        // Ustawia nowy zakres mo�liwych priorytet�w

    bool find(const T& element) const;                      // metoda do znajdowania elementu
    bool remove(const T& element);                          // Usuni�cie konkretnego elementu
    void buildFromFile(const std::string& filename);        // Budowanie z pliku
    void createRandom(size_t size);                         // Tworzenie losowej struktury
    void display() const;                                   // Wy�wietlanie zawarto�ci kolejki
    void clear();                                           // Czyszczenie kolejki

};

// Wymuszenie instancjacji szablonu
extern template class HeapPrioQueue<int>;
extern template class HeapPrioQueue<double>;
extern template class HeapPrioQueue<std::string>;

#endif // HEAP_PRIO_QUEUE_H