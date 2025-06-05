#ifndef QUEUEPAIR_H
#define QUEUEPAIR_H

#include <queue>
#include <vector>

class QueuePair {
private:
    std::queue<std::pair<int, int>> data; 

public:
    void procesarVector(std::vector<int> vec);
    void imprimirQueue();
};

#endif 
