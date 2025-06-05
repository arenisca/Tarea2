#include "queuePair.h"
#include <iostream>

void QueuePair::procesarVector(std::vector<int> vec) {
    if (vec.empty())
        return;

    int current = vec[0];
    int count = 1;

    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] == current) {
            ++count;
        } else {
            data.push(std::make_pair(current, count));
            current = vec[i];
            count = 1;
        }
    }

    data.push(std::make_pair(current, count));
}

void QueuePair::imprimirQueue() {
    while (!data.empty()) {
        std::pair<int, int> pair = data.front();
        std::cout << pair.second << " " << pair.first << "'s ";
        data.pop();
    }
    std::cout << std::endl;
}
