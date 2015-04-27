/*
 *  File: LinkedPriorityQueue.cpp
 *  - - - - - - - - - - - - - - -
 *  This file implements the LinkedPriorityQueue class,
 *  which allows for fast enqueueing of a PriorityQueue,
 *  but slower dequeueing.
 */

#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    head = new ListNode;
    head->next = NULL;
}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    ListNode *node = head;
    while(!node) {
        ListNode *nextNode = node->next;
        delete node;
        node = nextNode;
    }
}

void LinkedPriorityQueue::clear() {
    ListNode *node = head->next;
    while(!node) {
        ListNode *nextNode = node->next;
        delete node;
        node = nextNode;
    }
    head->next = NULL;
}

string LinkedPriorityQueue::dequeue() {
    if(head->next == NULL) error("The queue is empty");
    ListNode *toDequeue = head->next;
    string value = toDequeue->value;
    if(toDequeue->next != NULL) {
        toDequeue->next->prev = head;
        head->next = toDequeue->next;
    } else {
        head->next = NULL;
    }
    delete toDequeue;
    return value;
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    ListNode *insert = new ListNode;
    insert->value = value;
    insert->priority = priority;
    for(ListNode *node = head->next; node != NULL; node = node->next) {
        /*
         *  Since ListNode has built-in operators that
         *  determine equality, simply use the
         *  value of the ListNode referenced by the pointer
         */
        if(*insert < *node) {
            insert->prev = node->prev;
            insert->next = node;
            node->prev->next = insert;
            node->prev = insert;
            break;
        }
        if(*insert >= *node && node->next == NULL) {
            insert->prev = node;
            node->next = insert;
            break;
        }
    }
    if(head->next == NULL) {
        head->next = insert;
        insert->prev = head;
    }
}

bool LinkedPriorityQueue::isEmpty() const {
    return head->next == NULL;
}

string LinkedPriorityQueue::peek() const {
    if(head->next == NULL) error("The queue is empty");
    return head->next->value;
}

int LinkedPriorityQueue::peekPriority() const {
    if(head->next == NULL) error("The queue is empty");
    return head->next->priority;
}

int LinkedPriorityQueue::size() const {
    int count = 0;
    for(ListNode *node = head->next; node != NULL; node = node->next) {
        count++;
    }
    return count;
}
