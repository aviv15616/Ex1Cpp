// Author: anksilae@gmail.com

#ifndef STACK_H
#define STACK_H

class Stack {
private:
    int capacity;
    int top;
    int* arr;

public:
    Stack(int capacity);
    ~Stack();

    void push(int val);
    int pop();
    bool isEmpty();
    bool isFull();
    void print() const;
};

#endif
