/*
 *  File: VectorPriorityQueue.cpp
 *  - - - - - - - - - - - - - - -
 *  This file implements the VectorPriorityQueue class,
 *  which allows for fast enqueueing of a PriorityQueue,
 *  but slower dequeueing.
 */

#include "VectorPriorityQueue.h"

VectorPriorityQueue::VectorPriorityQueue() {

}

VectorPriorityQueue::~VectorPriorityQueue() {
    
}

void VectorPriorityQueue::clear() {
    unsortedVector.clear();
}

string VectorPriorityQueue::dequeue() {
    if(unsortedVector.size() == 0) error("The queue is empty");
    int urgPriorityIndex = returnUrgentPriorityIndex();
    string value = unsortedVector[urgPriorityIndex].value;
    unsortedVector.remove(urgPriorityIndex);
    return value;
}

void VectorPriorityQueue::enqueue(string value, int priority) {
    PQEntry e = {value, priority};
    unsortedVector.add(e);
}

bool VectorPriorityQueue::isEmpty() const {
    return unsortedVector.isEmpty();
}

string VectorPriorityQueue::peek() const {
    if(unsortedVector.size() == 0) error("The queue is empty ");
    int urgPriorityIndex = returnUrgentPriorityIndex();
    string value = unsortedVector[urgPriorityIndex].value;
    return value;
}


int VectorPriorityQueue::peekPriority() const {
    if(unsortedVector.size() == 0) error("The queue is empty ");
    int urgPriorityIndex = returnUrgentPriorityIndex();
    int urgPriority = unsortedVector[urgPriorityIndex].priority;
    return urgPriority;
}

int VectorPriorityQueue::size() const {
    return unsortedVector.size();
}

int VectorPriorityQueue::returnUrgentPriorityIndex() const {
    int urgPriorityIndex = 0;
    for(int i = 0; i < unsortedVector.size(); i++) {
        if(i != urgPriorityIndex) {
            int urgPriority = unsortedVector[urgPriorityIndex].priority;
            int currPriority = unsortedVector[i].priority;
            /*
             *  Since each VectorPriorityQueue item is a PQEntry,
             *  we can use the built-in operators for equality
             *  to compare one PQEntry to another.
             */
            if(urgPriority > currPriority) {
                urgPriorityIndex = i;
            } else if(urgPriority == currPriority) {
                string urgPriorityValue = unsortedVector[urgPriorityIndex].value;
                string currPriorityValue = unsortedVector[i].value;
                if(urgPriorityValue > currPriorityValue) urgPriorityIndex = i;
            }
        }
    }
    return urgPriorityIndex;
}