// Author: anksilae@gmail.com

#include "PriorityQueue.hpp"
#include <iostream>
#include <stdexcept>

PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("PriorityQueue capacity must be greater than 0.");
    }
    heap = new Node[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

// **Heapify Up**
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].value <= heap[index].value) break;  
        std::swap(heap[parent], heap[index]);
        index = parent;
    }
}

// **Heapify Down**
void PriorityQueue::heapifyDown(int index) {
    while (2 * index + 1 < size) {  
        int left = 2 * index + 1, right = 2 * index + 2, smallest = left;
        
        if (right < size && heap[right].value < heap[left].value) 
            smallest = right;

        if (heap[index].value <= heap[smallest].value) break;
        
        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

// **Insert with Dynamic Growth**
void PriorityQueue::insert(int key, int value) {
    if (size == capacity) {  // Increase size dynamically
        capacity *= 2;
        Node* newHeap = new Node[capacity];
        for (int i = 0; i < size; ++i) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
    }
    
    heap[size] = {key, value};
    heapifyUp(size);
    size++;
}

// **Extract Min**
int PriorityQueue::extractMin() {
    if (isEmpty()) {
        throw std::underflow_error("PriorityQueue is empty. Cannot extract minimum.");
    }

    int minValue = heap[0].key;
    heap[0] = heap[size - 1];  // Replace root with last element
    size--;
    heapifyDown(0);

    return minValue;
}

// **Decrease Key**
void PriorityQueue::decreaseKey(int key, int newValue) {
    for (int i = 0; i < size; ++i) {
        if (heap[i].key == key) {
            if (heap[i].value > newValue) {
                heap[i].value = newValue;
                heapifyUp(i);
            }
            return;
        }
    }
}
void PriorityQueue::print() const {
    // יצירת עותק זמני
    Node* copy = new Node[size];
    for (int i = 0; i < size; ++i) {
        copy[i] = heap[i];
    }

    // מיון לפי value (ascending)
    for (int i = 0; i < size - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (copy[j].value < copy[minIdx].value) {
                minIdx = j;
            }
        }
        Node temp = copy[i];
        copy[i] = copy[minIdx];
        copy[minIdx] = temp;
    }

    // הדפסה
    std::cout << "[ ";
    for (int i = 0; i < size; ++i) {
        std::cout << "(" << copy[i].key << ", " << copy[i].value << ") ";
    }
    std::cout << "]\n";

    delete[] copy;
}


