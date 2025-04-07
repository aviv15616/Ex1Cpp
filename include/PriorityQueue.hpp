// Author: anksilae@gmail.com

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

class PriorityQueue {
private:
    struct Node {
        int key, value;
    };

    Node* heap;
    int* positionMap; // Maps keys to their index in the heap for O(log n) decreaseKey
    int capacity, size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue(int cap);
    ~PriorityQueue();

    bool isEmpty() const;
    void insert(int key, int value);
    int extractMin();
    void decreaseKey(int key, int newValue);
    void print() const;
};

#endif
