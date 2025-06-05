#ifndef CIRCULARARRAYQUEUE
#define CIRCULARARRAYQUEUE

#include "QueueADT.h"

class CircularArrayQueue {
    private:
        int head;
        int tail;
        int* arr;
        int capacity;
        int count;
        bool isFull();

    public:
        CircularArrayQueue(int size);
        ~CircularArrayQueue();
        void enqueue(int item);
        void dequeue();
        int front();
        bool isEmpty();
        int size();
};

#endif