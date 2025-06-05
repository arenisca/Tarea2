#include <iostream>
#include <vector>
#include "queuePair.h"

int main() {
    std::vector<int> vec = {1, 1, 1, 1, 1, 6, 6, 6, 7, 7, 7, 8, 8};

    QueuePair counter;
    counter.procesarVector(vec);

    std::cout << "EJEMPLO DE QUEUE: ";
    counter.imprimirQueue();

    return 0;
}
