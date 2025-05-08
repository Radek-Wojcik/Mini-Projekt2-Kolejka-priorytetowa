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

