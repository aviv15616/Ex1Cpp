#include "Queue.h"
#include <iostream>
#include <stdexcept> 
#include <sstream>

Queue::Queue(int capacity): capacity(capacity), front(0), rear(0), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Queue capacity must be greater than 0.");
    }
    arr = new int[capacity];
}

Queue::~Queue() {
    delete[] arr;
}

void Queue::push(int val) {
    if (isFull()) {
        std::ostringstream oss;
        oss << "Queue is full. Cannot insert " << val << ".";
        throw std::invalid_argument(oss.str());
    }
    arr[rear] = val;
    rear = (rear + 1) % capacity;
    size++;
}

int Queue::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty. Cannot remove element.");
    }
    int result = arr[front];
    front = (front + 1) % capacity;
    size--;
    return result;
}

// **New popBack function for LIFO behavior (simulating a stack)**
int Queue::popBack() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty. Cannot remove element.");
    }
    rear = (rear - 1 + capacity) % capacity;  // Move rear backward
    int result = arr[rear];
    size--;
    return result;
}

bool Queue::isEmpty() {
    return size == 0;
}

bool Queue::isFull() {
    return size == capacity;
}
