// Author: anksilae@gmail.com

#include "Queue.hpp"
#include <iostream>
#include <stdexcept>

Queue::Queue(int capacity) {
    this->capacity = capacity;
    front = 0;
    size = 0;
    arr = new int[capacity];
}

Queue::~Queue() {
    delete[] arr;
}

void Queue::push(int val) {
    if (isFull()) {
        throw std::overflow_error("Queue overflow");
    }
    int rear = (front + size) % capacity;
    arr[rear] = val;
    size++;
}

int Queue::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Queue underflow");
    }
    int val = arr[front];
    front = (front + 1) % capacity;
    size--;
    return val;
}

bool Queue::isEmpty() {
    return size == 0;
}

bool Queue::isFull() {
    return size == capacity;
}
void Queue::print() const {
    std::cout << "[ ";
    for (int i = 0; i < size; ++i) {
        int index = (front + i) % capacity;
        std::cout << arr[index] << " ";
    }
    std::cout << "]\n";
}
