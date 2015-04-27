/*
 *  File: HeapPriorityQueue.h
 *  - - - - - - - - - - - - - - -
 *  This file exports the HeapPriorityQueue,
 *  which allows for dequeuing and enqueueing
 *  in logarithmic time since order is maintained
 *  in a binomial tree.
 */

#ifndef _heappriorityqueue_h
#define _heappriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
#include "error.h"
using namespace std;

/*
 *  Class: HeapPriorityQueue
 *  - - - - - - - - - - - - - - -
 *  This class maintains an ordered set of values
 *  that can return pre-prioritized values
 *  using its helper functions. It is designed for
 *  dequeueing and enqueueing in logarithmic time.
 */
class HeapPriorityQueue {
public:
    /*
     *  Constructor: HeapPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Initializes a new HeapPriorityQueue. Since
     *  this class uses a C-style array to maintain order,
     *  this initializes the array used in the
     *  binomial tree.
     */
    HeapPriorityQueue();
    
    /*
     *  Destructor: ~HeapPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by BinomialPriorityQueue,
     *  which requires the deletion of the array that
     *  maintains the binomial tree.
     */
    ~HeapPriorityQueue();
    
    /*
     *  Method: clear
     *  - - - - - - - - - - - - - - - - - -
     *  Removes all items from HeapPriorityQueue. Since
     *  this class uses an array, this requires
     *  each entry in the array to nullified.
     */
    void clear();

    /*
     *  Method: dequeue
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue and also removes it from the queue.
     *  Since a binomial tree is used, it simply returns
     *  the highest priority value atop the tree, but then
     *  has to reorder the rest of the tree now that global
     *  root is removed.  To do this, it takes the lowest priority
     *  branch, moves it to the top of the tree, and then 
     *  rearranges it accordingly.
     */
    string dequeue();

    /*
     *  Method: enqueue
     *  Parameters: string value
     *              int priority
     *  - - - - - - - - - - - - - - - - - -
     *  Adds a user-defined item to the PriorityQueue given
     *  the item's key and its corresponding priority level, which is
     *  used for retrieval. Since a binomial tree is used,
     *  the value is enqueued as if it is the lowest priority branch,
     *  and then moved up in the tree based on comparison with its
     *  parent node.
     */
    void enqueue(string value, int priority);

    /*
     *  Method: isEmpty
     *  - - - - - - - - - - - - - - - - - -
     *  Determines whether the PriorityQueue is empty.
     *  This uses a member variable of the HeapPriorityQueue
     *  class that counts each instance when something is
     *  enqueued or disqueued.
     */
    bool isEmpty() const;

    /*
     *  Method: peek
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a binomial tree is employed, this is as simple as
     *  calling the key value from the top of the list.
     */
    string peek() const;

    /*
     *  Method: peekPriority
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the priority of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a binomial tree is employed, this is as simple as
     *  calling the key value from the top of the list.
     */
    int peekPriority() const;

    /*
     *  Method: size
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the size of the PriorityQueue.
     *  This uses a member variable of the HeapPriorityQueue
     *  class that counts each instance when something is
     *  enqueued or disqueued.
     */
    int size() const;

private:
    /*
     *  Method: expandQueueCapacity
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function increases the capacity of
     *  the C-style array used by twice the capacity
     *  as specified in the constant member variable,
     *  kInititalCapacity.
     */
    void expandQueueCapacity();

    /*
     *  Method: percolateUp
     *  Parameters: int index
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function determines whether the newly
     *  enqueued value should assume a higher priority
     *  in the binomial tree.  Since it is either a child or
     *  the sole root, it needs to only check its parent's
     *  priority and then swap places if indeed higher priority.
     */
    void percolateUp(int childIndex);

    /*
     *  Method: trickleDown
     *  Parameters: int lastNodeIndex
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function reorders the binomial
     *  tree after it has recently been dequeued.
     *  It does so by taking the lowest priority branch
     *  and swapping it with the highest priority root
     *  position in tree. It then checks all of its
     *  new children to see if it is lower priority,
     *  and swaps places accordingly.
     */
    void trickleDown(int lastNodeIndex);

    /*
     *  Method: swap
     *  Parameters: PQEntry& childNode
     *              PGEntry& trickleDownNode
     *              int childIndex
     *              int trickleDownIndex
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function swaps two nodes
     *  in the binomial tree class given their values
     *  and index locations within the tree.
     */
    void swap(PQEntry& childNode, PQEntry& trickleDownNode, int childIndex, int& trickleDownIndex);

    /*
     *  Method: getLeftChildIndex
     *  Parameters: int index
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function returns the lefthand
     *  child index of a given parent index based
     *  on the binomial tree used.
     */
    int getLeftChildIndex(int index) const;

    /*
     *  Method: getRightChildIndex
     *  Parameters: int index
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function returns the righthand
     *  child index of a given parent index based
     *  on the binomial tree used.
     */
    int getRightChildIndex(int index) const;

    /*
     *  Method: setRoot
     *  Parameters: int index
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function returns a tree branch
     *  that is in bounds if the branch exists in the tree,
     *  or returns a null branch if it doesn't.
     */
    PQEntry setRoot(int index);

    /*
     *  Method: validBranch
     *  Parameters: PQEntry& root
     *  - - - - - - - - - - - - - - - - - -
     *  This helper function is a substitute
     *  for the == operator that isn't exported
     *  in the PQEntry class.
     */
    bool validBranch(PQEntry& root);

    /*
     *  Array: queue
     *  - - - - - - - - - - - - - - - - - -
     *  C-style array used to house the binomial
     *  tree. It is initialized in the constructor
     *  and deleted in the destructor.
     */
    PQEntry *queue;

    /*
     *  Integer: kInitialCapacity
     *  - - - - - - - - - - - - - -
     *  Initial size of C-style array. Also
     *  used on additional enlargements of array.
     */
    static const int kInitialCapacity = 10;

    /*
     *  Integer: kZeroBaseOffset
     *  - - - - - - - - - - - - - -
     *  Offset used by adopting a 1-based array.
     */
    static const int kZeroBaseOffset = 1;

    /*
     *  Integer: queueCapacity
     *  - - - - - - - - - - - - - -
     *  Max size of array.
     */
    int queueCapacity;
    
    /*
     *  Integer: kZeroBaseOffset
     *  - - - - - - - - - - - - - -
     *  Current number of items in array.
     */
    int queueSize;
};

#endif
