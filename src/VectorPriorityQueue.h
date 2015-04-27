/*
 *  File: VectorPriorityQueue.h
 *  - - - - - - - - - - - - - - -
 *  This file exports the VectorPriorityQueue,
 *  which allows for fast enqueueing of a PriorityQueue,
 *  but slower dequeueing.
 */

#ifndef _vectorpriorityqueue_h
#define _vectorpriorityqueue_h

#include <iostream>
#include <string>
#include "vector.h"
#include "PQEntry.h"
#include "error.h"
using namespace std;

/*
 *  Class: VectorPriorityQueue
 *  - - - - - - - - - - - - - - -
 *  This class maintains an unordered set of values
 *  that can return pre-prioritized values
 *  using its helper functions. It is designed for
 *  fast enqueueing in constant time, but has
 *  poor performance in return values in linear time.
 */
class VectorPriorityQueue {
public:
    /*
     *  Constructor: VectorPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  'Initializes' a new VectorPriorityQueue. Since
     *  this class uses the Vector library, this doesn't
     *  do much.
     */
    VectorPriorityQueue();

    /*
     *  Destructor: ~VectorPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by VectorPriorityQueue.
     */
    ~VectorPriorityQueue();

    /*
     *  Method: clear
     *  - - - - - - - - - - - - - - - - - -
     *  Removes all items from VectorPriorityQueue. Since
     *  this class uses the Vector library, this simply
     *  leverages the clear() function from that class
     *  to carry out the same job.
     */
    void clear();

    /*
     *  Method: dequeue
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue and also removes it from the queue.
     *  It calls on a helper function, detailed in the private section,
     *  to loop through the associated values and find the one
     *  with the highest priority, returning its index to 
     *  to the calling function for use in the PriorityQueue.
     */
    string dequeue();

    /*
     *  Method: enqueue
     *  Parameters: string value
     *              int priority
     *  - - - - - - - - - - - - - - - - - -
     *  Adds a user-defined item to the PriorityQueue given
     *  the item's key and its corresponding priority level, which is
     *  used for retrieval. Since this queue does not respect
     *  order upon enqueueing, this function simply uses the
     *  Vector library's add function to store the value at 
     *  the end of the queue.
     */
    void enqueue(string value, int priority);

    /*
     *  Method: isEmpty
     *  - - - - - - - - - - - - - - - - - -
     *  Determines whether the PriorityQueue is empty.
     *  PriorityQueue and also removes it from the queue.
     *  It calls on a helper function detailed in the private section,
     *  to loop through the associated values and find the one
     *  with the highest priority, returning its index to 
     *  to the calling function for use in the PriorityQueue.
     */
    bool isEmpty() const;

    /*
     *  Method: peek
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue without removing it.
     *  It calls on a helper function, detailed in the private section,
     *  to loop through the associated values and find the one
     *  with the highest priority, returning its index to 
     *  to the calling function for use in the PriorityQueue.
     */
    string peek() const;

    /*
     *  Method: peekPriority
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the priority of the highest priority item in the
     *  PriorityQueue without removing it.
     *  It calls on a helper function, detailed in the private section,
     *  to loop through the associated values and find the one
     *  with the highest priority, returning its index to 
     *  to the calling function for use in the PriorityQueue.
     */    
    int peekPriority() const;

    /*
     *  Method: size
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the size of the PriorityQueue.
     *  Leveraging the Vector library means this
     *  function can just call on the size function
     *  in that library.
     */ 
    int size() const;

private:

    /*
     *  Method: returnUrgentPriorityIndex
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the index within the PriorityQueue, housed in a Vector,
     *  for the highest priority item therein. It does so
     *  by looping through each item in the queue and measuring it
     *  against the current highest priority item held locally in
     *  the function.
     */
    int returnUrgentPriorityIndex() const;

    /*
     *  Object: unsortedVector
     *  - - - - - - - - - - - - -
     *  The data type for the PriorityQueue that houses
     *  the specific struct uses for the queue's items.
     *  A vector is used for fast enqueueing.
     */
    Vector<PQEntry> unsortedVector;
};

#endif
