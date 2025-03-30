#ifndef QUEUE_H
#define QUEUE_H

class Queue {
    private:
        int capacity; 
        int front;
        int rear;
        int size;
        int* arr;
    
public:
    Queue(int capacity);
    ~Queue();

    void push(int val);
    int pop();
    bool isEmpty();
    bool isFull();
    int popBack();
};

#endif
