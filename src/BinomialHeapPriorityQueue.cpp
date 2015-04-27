/*
 *  File: BinomialPriorityQueue.cpp
 *  - - - - - - - - - - - - - - -
 *  This file implements the BinomialPriorityQueue,
 *  which allows for dequeuing and enqueueing
 *  in logarthmic time since order is maintained
 *  in a binomial heap.
 */

#include "BinomialHeapPriorityQueue.h"

BinomialHeapPriorityQueue::BinomialHeapPriorityQueue() {

}

BinomialHeapPriorityQueue::~BinomialHeapPriorityQueue() {

}

void BinomialHeapPriorityQueue::clear() {
    heap.clear();
}

string BinomialHeapPriorityQueue::dequeue() {
    if(heap.size() == 0) error("The queue is empty");
    int dequeuedRootIndex = 0;
    BinomialHeapNode* dequeuedRoot = NULL;
    getDequeuedRoot(dequeuedRoot, dequeuedRootIndex);
    string value = dequeuedRoot->entry.value;
    Vector<BinomialHeapNode *> orphanedChildren = heap[dequeuedRootIndex]->children;
    heap.remove(dequeuedRootIndex);
    merge(orphanedChildren, heap);
    return value;
}

void BinomialHeapPriorityQueue::enqueue(string value, int priority) {
    Vector<BinomialHeapNode* > newHeap;
    BinomialHeapNode* newTree = new BinomialHeapNode;
    PQEntry newNode = {value, priority};
    Vector<BinomialHeapNode* > newChildren;
    newTree->entry = newNode;
    newTree->children;
    newHeap.add(newTree);
    merge(newHeap, heap);
}

bool BinomialHeapPriorityQueue::isEmpty() const {
    return heap.size() == 0;
}

string BinomialHeapPriorityQueue::peek() const {
    if(heap.size() == 0) error("The queue is empty");    
    int dequeuedRootIndex = 0;
    BinomialHeapNode* dequeuedRoot = NULL;
    getDequeuedRoot(dequeuedRoot, dequeuedRootIndex);
    return dequeuedRoot->entry.value;
}

int BinomialHeapPriorityQueue::peekPriority() const {
    if(heap.size() == 0) error("The queue is empty");
    int dequeuedRootIndex = 0;
    BinomialHeapNode* dequeuedRoot = NULL;
    getDequeuedRoot(dequeuedRoot, dequeuedRootIndex);
    return dequeuedRoot->entry.priority;
}

int BinomialHeapPriorityQueue::size() const {
    int heapSize = 0;
    for(int i = 0; i < heap.size(); i++) {
        if(heap[i] != NULL) heapSize += power(2, i);
    }
    return heapSize;
}

void BinomialHeapPriorityQueue::merge(Vector<BinomialHeapNode *>& heap1, Vector<BinomialHeapNode* >& heap2) {
    Vector<BinomialHeapNode *> mergedHeap;
    BinomialHeapNode* carry = NULL;
    for(int i = 0; i < ((heap1.size() > heap2.size()) ? heap1.size() : heap2.size()); i++) {
        Vector<BinomialHeapNode *> possibleTrees;
        if(inBounds(heap1, i) && heap1[i]) possibleTrees.add(heap1[i]);
        if(inBounds(heap2, i) && heap2[i]) possibleTrees.add(heap2[i]);
        if(carry) possibleTrees.add(carry);
        if(possibleTrees.size() == 0) {
            mergedHeap.add(NULL);
            carry = NULL;
        } else if(possibleTrees.size() == 1) {
            mergedHeap.add(possibleTrees[0]);
            carry = NULL;
        } else if(possibleTrees.size() == 2) {
            mergedHeap.add(NULL);
            mergeTrees(carry, possibleTrees[0], possibleTrees[1]);
        } else {
            mergedHeap.add(possibleTrees[2]);
            mergeTrees(carry, possibleTrees[0], possibleTrees[1]);
        }
    }
    if(carry) mergedHeap.add(carry);
    heap2 = mergedHeap;
}

bool BinomialHeapPriorityQueue::inBounds(Vector<BinomialHeapNode *>& heap, int index) {
    return (heap.size() - 1) >= index;
}

void BinomialHeapPriorityQueue::mergeTrees(BinomialHeapNode* & newTree, BinomialHeapNode* &tree1, BinomialHeapNode* &tree2) {
    if(tree1->entry >= tree2->entry) {
        tree2->children.add(tree1);
        newTree = tree2;
    } else {
        tree1->children.add(tree2);
        newTree = tree1;
    }
}

void BinomialHeapPriorityQueue::getDequeuedRoot(BinomialHeapNode*& dequeuedRoot, int& dequeuedRootIndex) const {
    for(int i = 0; i < heap.size(); i++) {
        if(heap[i]) {
            if(!dequeuedRoot || dequeuedRoot->entry >= heap[i]->entry) {
                dequeuedRootIndex = i;
                dequeuedRoot = heap[i];
            }
        }
    }
}

int BinomialHeapPriorityQueue::power(int base, int exponent) const {
    int result = 1;
    for(int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}
