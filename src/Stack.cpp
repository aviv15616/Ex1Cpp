// Author: anksilae@gmail.com

#include "Stack.hpp"
#include <iostream>
#include <stdexcept>

Stack::Stack(int capacity) {
    this->capacity = capacity;
    this->top = -1;
    arr = new int[capacity];
}

Stack::~Stack() {
    delete[] arr;
}

void Stack::push(int val) {
    if (isFull()) {
        throw std::overflow_error("Stack overflow");
    }
    arr[++top] = val;
}

int Stack::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack underflow");
    }
    return arr[top--];
}

bool Stack::isEmpty() {
    return top == -1;
}

bool Stack::isFull() {
    return top == capacity - 1;
}
void Stack::print() const {
    std::cout << "[ ";
    for (int i = top; i >= 0; --i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]\n";
}


