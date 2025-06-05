#include <string>
#include <vector>
#include <iostream>

class priorityQueue {
private:
    std::vector<int> heap;

    int parent(int i) {
      return (i-1) / 2;
    }

    int leftChild(int i) {
        return 2 * i + 1;
    }

    int rightChild(int i) {
        return 2 * i + 2;
    }

    void heapUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapDown(int i) {
        int maxIndex = i;
        int l = leftChild(i);
        int r = rightChild(i);

        if (l <= heap.size() && heap[maxIndex] > heap[l]) {
            maxIndex = l;
        }

        if (r <= heap.size() && heap[maxIndex] > heap[r]) {
            maxIndex = r;
        }

        if (i != maxIndex) {
            std::swap(heap[i], heap[maxIndex]);
            heapDown(maxIndex);
        }
    }

public:
    priorityQueue() {}
    ~priorityQueue() {
      heap.clear();
    }
    
    void insert(int value) {
        //Se ingresa un elemento  luego se llama a heapUp para reajustar la cola de prioridad
        heap.push_back(value);
        heapUp(heap.size() - 1);
    }

    int getPriority() {
        //se retorna la raiz
        return heap[0];
    }

    int extractPriority() {
        //se intercambia la raiz con el ultimo elemento y se elimina el ultimo elemento
        int priority = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        //Luego se llama hepDown para reajustar la cola de prioridad
        heapDown(0);
        return priority;
    }

    bool isEmpty() {
        return heap.size() == 0;
    }
};
