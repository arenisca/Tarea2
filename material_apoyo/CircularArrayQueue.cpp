#include "CircularArrayQueue.h"
#include <iostream>

CircularArrayQueue::CircularArrayQueue(int size) {
    arr = new int[size];
    capacity = size;
    head = 0;
    tail = -1;
    count = 0;
}

CircularArrayQueue::~CircularArrayQueue() {
    delete[] arr;
}

void CircularArrayQueue::enqueue(int item) {
    if (isFull()) {
        int newCapacity = 2 * capacity;
        int* newArr = new int[newCapacity];

        for (int i = 0; i < capacity; i++) {
            newArr[i] = arr[(head + i) % capacity];
        }
        delete[] arr;

        arr = newArr;
        capacity = newCapacity;
        head = 0;
        tail = count - 1;
    }

    // Agregar el nuevo elemento
    tail = (tail + 1) % capacity;
    arr[tail] = item;
    count++;
}

void CircularArrayQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "La cola está vacía\n";
        return;
    }
    head = (head + 1) % capacity;
    count--;
}

int CircularArrayQueue::front() {
    if (isEmpty()) {
        std::cout << "La cola está vacía\n";
        return -1;
    }
    return arr[head];
}

bool CircularArrayQueue::isEmpty() {
    return (count == 0);
}

bool CircularArrayQueue::isFull() {
    return (count == capacity);
}

int CircularArrayQueue::size() {
    return count;
}