/*
 *  File: LinkedPriorityQueue.h
 *  - - - - - - - - - - - - - - -
 *  This file exports the LinkedPriorityQueue,
 *  which allows for fast dequeueing of a PriorityQueue,
 *  but longer enqueueing.
 */

#ifndef _linkedpriorityqueue_h
#define _linkedpriorityqueue_h

#include <cstddef>    // for NULL
#include <iostream>
#include <string>
#include "ListNode.h"
#include "PQEntry.h"
#include "error.h"
using namespace std;

/*
 *  Class: LinkedPriorityQueue
 *  - - - - - - - - - - - - - - -
 *  This class maintains an ordered set of values
 *  that can return pre-prioritized values
 *  using its helper functions. It is designed for
 *  fast dequeueing in constant time, but is
 *  slower to enqueue in linear time.
 */
class LinkedPriorityQueue {
public:
    /*
     *  Constructor: LinkedPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Initializes a new LinkedPriorityQueue. Since
     *  this class uses a LinkedList to maintain order,
     *  this initializes the ListNode struct referenced
     *  by the private section's pointer.
     */
    LinkedPriorityQueue();
    
    /*
     *  Destructor: ~LinkedPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by LinkedPriorityQueue,
     *  which requires the deletion of all ListNodes created
     *  to maintain the queue.
     */
    ~LinkedPriorityQueue();

    /*
     *  Method: clear
     *  - - - - - - - - - - - - - - - - - -
     *  Removes all items from LinkedPriorityQueue. Since
     *  this class uses a LinkedList, this requires
     *  each ListNode created to maintain order to be
     *  deleted.
     */    
    void clear();

    /*
     *  Method: dequeue
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue and also removes it from the queue.
     *  Since a LinkedList orders the items by highest priority descending,
     *  this simply needs to dequeue the item right after the
     *  LinkedList's head.
     */
    string dequeue();

    /*
     *  Method: enqueue
     *  Parameters: string value
     *              int priority
     *  - - - - - - - - - - - - - - - - - -
     *  Adds a user-defined item to the PriorityQueue given
     *  the item's key and its corresponding priority level, which is
     *  used for retrieval. Since this queue respects order,
     *  each enqueued must loop through the entirety of the list, and
     *  if it finds its place in between two ListNodes, it must ensure
     *  to insert itself without losing the corresponding memory
     *  addresses for each side of the chain.
     */
    void enqueue(string value, int priority);

    /*
     *  Method: isEmpty
     *  - - - - - - - - - - - - - - - - - -
     *  Determines whether the PriorityQueue is empty.
     *  This can be done by checking if the Head of the
     *  Linked List is linked to any other node in the chain.
     */
    bool isEmpty() const;

    /*
     *  Method: peek
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a LinkedList is employed, this is as simple as
     *  calling the key value from the first node after the Head.
     */
    string peek() const;
    
    /*
     *  Method: peekPriority
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the priority of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a LinkedList is employed, this is as simple as
     *  calling the key value from the first node after the Head.
     */
    int peekPriority() const;

    /*
     *  Method: size
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the size of the PriorityQueue.
     *  A Linked List requires this function to loop through
     *  all of its entries and count them, returning the
     *  counter as the size.
     */
    int size() const;

private:

    /*
     *  ListNode Pointer: head
     *  - - - - - - - - - - - - -
     *  The Head of the Linked List that determines
     *  its start, for which all subsequent entries
     *  connect. The pointer is initially set to null
     *  and initialized in the constructor.
     */
    ListNode *head = NULL;
};

#endif
