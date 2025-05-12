#include <iostream>
#include "heap_prio_queue.h"

int main() {
    HeapPrioQueue<int> queue(1, 1000);

    queue.insert(5, 100);   // Element 5 z priorytetem 100
    queue.display();
    queue.insert(10, 50);   // Element 10 z priorytetem 50
    queue.display();
    queue.insert(15, 200);  // Element 15 z priorytetem 200

    queue.display();

    std::cout << "Element o najwyzszym priorytecie: " << queue.findMax() << std::endl;

    int max = queue.extractMax();
    std::cout << "Usuniety element o najwyzszym priorytecie: " << max << std::endl;

    queue.display();

    return 0;
}