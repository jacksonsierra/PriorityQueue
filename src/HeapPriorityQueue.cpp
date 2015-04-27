/*
 *  File: HeapPriorityQueue.cpp
 *  - - - - - - - - - - - - - - -
 *  This file implements the HeapPriorityQueue,
 *  which allows for dequeuing and enqueueing
 *  in logarithmic time since order is maintained
 *  in a binomial tree.
 */

#include "HeapPriorityQueue.h"

HeapPriorityQueue::HeapPriorityQueue() {
    queueCapacity = kInitialCapacity;
    queue = new PQEntry[queueCapacity];
    queueSize = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] queue;
}

void HeapPriorityQueue::clear() {
    for(int i = 0; i < queueSize; i++) {
        queue[i] = {};
    }
    queueSize = 0;
}

string HeapPriorityQueue::dequeue() {
    if(queueSize == 0) error("The queue is empty");
    string value = queue[kZeroBaseOffset].value;
    int lastNodeIndex = queueSize;
    trickleDown(lastNodeIndex);
    queueSize--;
    return value;
}

void HeapPriorityQueue::enqueue(string value, int priority) {
    PQEntry newNode = {value, priority};
    int newNodeIndex = queueSize + kZeroBaseOffset;
    if(queueCapacity <= newNodeIndex) expandQueueCapacity();
    queue[newNodeIndex] = newNode;
    queueSize++;
    if(newNodeIndex != kZeroBaseOffset) percolateUp(newNodeIndex);
}

bool HeapPriorityQueue::isEmpty() const {
    return queueSize == 0;
}

string HeapPriorityQueue::peek() const {
    if(queueSize == 0) error("The queue is empty");
    return queue[kZeroBaseOffset].value;
}

int HeapPriorityQueue::peekPriority() const {
    if(queueSize == 0) error("The queue is empty");
    return queue[kZeroBaseOffset].priority;
}

int HeapPriorityQueue::size() const {
    return queueSize;
}

void HeapPriorityQueue::expandQueueCapacity() {
    PQEntry *oldQueue = queue;
    queueCapacity *= 2;
    queue = new PQEntry[queueCapacity];
    queue[0] = {};
    for(int i = 1; i < queueSize + kZeroBaseOffset; i++) {
        queue[i] = oldQueue[i];
    }
    delete[] oldQueue;
}

void HeapPriorityQueue::percolateUp(int childIndex) {
    int parentIndex = childIndex / 2;
    PQEntry child = setRoot(childIndex);
    PQEntry parent = setRoot(parentIndex);
    while(validBranch(child) && child < parent) {
        queue[parentIndex] = child;
        queue[childIndex] = parent;
        childIndex = parentIndex;
        parentIndex = childIndex / 2;
        parent = queue[parentIndex];
    }
}

void HeapPriorityQueue::trickleDown(int lastNodeIndex) {
    int trickleDownIndex = kZeroBaseOffset;
    queue[trickleDownIndex] = queue[lastNodeIndex];  //Swap lowest priority with top root
    queue[lastNodeIndex] = {};
    PQEntry trickleDownNode = queue[trickleDownIndex];
    PQEntry leftChild = setRoot(getLeftChildIndex(trickleDownIndex));
    PQEntry rightChild = setRoot(getRightChildIndex(trickleDownIndex));
    /*
     *  Use PQEntry built-in operators for determining equality
     */
    while((validBranch(leftChild) && trickleDownNode > leftChild) ||
          (validBranch(rightChild) && trickleDownNode > rightChild)) {
        if(validBranch(rightChild) && leftChild > rightChild) {
            swap(rightChild, trickleDownNode, getRightChildIndex(trickleDownIndex), trickleDownIndex);
        } else {
            swap(leftChild, trickleDownNode, getLeftChildIndex(trickleDownIndex), trickleDownIndex);
        }
        leftChild = setRoot(getLeftChildIndex(trickleDownIndex));
        rightChild = setRoot(getRightChildIndex(trickleDownIndex));
    }
}

int HeapPriorityQueue::getLeftChildIndex(int index) const {
    return 2 * index;
}

int HeapPriorityQueue::getRightChildIndex(int index) const {
    return 2 * index + 1;
}

void HeapPriorityQueue::swap(PQEntry& childNode, PQEntry& trickleDownNode, int childIndex, int& trickleDownIndex) {
    queue[trickleDownIndex] = childNode;
    queue[childIndex] = trickleDownNode;
    trickleDownIndex = childIndex;
    trickleDownNode = queue[trickleDownIndex];
}

PQEntry HeapPriorityQueue::setRoot(int index) {
    PQEntry root;
    if(index <= queueSize) root = queue[index];
    return root;
}

bool HeapPriorityQueue::validBranch(PQEntry& root) {
    PQEntry blankRoot;
    return root != blankRoot;
}
