/*
 *  File: BinomialPriorityQueue.h
 *  - - - - - - - - - - - - - - -
 *  This file exports the BinomialPriorityQueue,
 *  which allows for dequeuing and enqueueing
 *  in logarithmic time since order is maintained
 *  in a binomial heap.
 */

#ifndef _BinomialHeapPriorityQueue_h
#define _BinomialHeapPriorityQueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
#include "Vector.h"
#include "error.h"
using namespace std;

/*
 *  Class: BinomialHeapPriorityQueue
 *  - - - - - - - - - - - - - - -
 *  This class maintains an ordered set of values
 *  that can return pre-prioritized values
 *  using its helper functions. It is designed for
 *  dequeueing and enqueueing in logarithmic time.
 */
class BinomialHeapPriorityQueue {
public:
    /*
     *  Constructor: BinomialHeapPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Initializes a new BinomialHeapPriorityQueue. Since
     *  this class maintains order using a struct and
     *  the Vector library, nothing is done in the
     *  constructor.
     */
    BinomialHeapPriorityQueue();
    
    /*
     *  Destructor: ~BinomialHeapPriorityQueue
     *  - - - - - - - - - - - - - - - - - -
     *  Frees any heap storage allocated by BinomialPriorityQueue,
     *  which is minimal given the Vector library employed.
     */
    ~BinomialHeapPriorityQueue();

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
     *  Since a binomial heap is used, this function loops
     *  through each of the roots of the heap's binomial trees
     *  to find the highest priority, using a helper function.
     *  It then calls on a different helper function to retain
     *  the child branches of the now dequeued root with
     *  highest priority, leveraging the merge functionality
     *  enumerated in the private section.
     */
    string dequeue();

    /*
     *  Method: enqueue
     *  Parameters: string value
     *              int priority
     *  - - - - - - - - - - - - - - - - - -
     *  Adds a user-defined item to the PriorityQueue given
     *  the item's key and its corresponding priority level, which is
     *  used for retrieval. Since a binomial heap is used,
     *  the value is turned into a binomial heap that is then merged
     *  with the larger binomial heap already in place, if applicable.
     *  The merge process occurs for each bionmial tree in either of the
     *  binomial heaps, and closely mirrors binary addition.
     */
    void enqueue(string value, int priority);

    /*
     *  Method: isEmpty
     *  - - - - - - - - - - - - - - - - - -
     *  Determines whether the PriorityQueue is empty.
     *  Since the binomial heap is maintained by the
     *  Vector library, this simply draws on its
     *  size function to return the associated boolean.
     */
    bool isEmpty() const;

    /*
     *  Method: peek
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the value of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a binomial heap is employed, this requires a
     *  helper function to loop through each root of the heap
     *  and determine and return the node with the highest priority.
     */
    string peek() const;

    /*
     *  Method: peekPriority
     *  - - - - - - - - - - - - - - - - - -
     *  Returns the priority of the highest priority item in the
     *  PriorityQueue without removing it.
     *  Since a binomial heap is employed, this requires a
     *  helper function to loop through each root of the heap
     *  and determine and return the node with the highest priority.
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
    struct BinomialHeapNode {
        PQEntry entry;
        Vector<BinomialHeapNode *> children;
    };

    /*
     *  Method: merge
     *  Parameters: Vector<BinomialHeapNode *>& heap1
     *              Vector<BinomialHeapNode *>& heap2
     *  - - - - - - - - - - - - - - - - - -
     *  Takes two heaps of any size as reference parameters and
     *  returns their syntheis by reference. This is accomplished
     *  by looping through each of the heap's roots and determining
     *  whether the offspring's respective element does or does not contains a tree.
     *  This process mirrors binary addition and introduces the
     *  help of a carry node to keep track of the combinations and potentially
     *  inserting into the final combination.
     */ 
    void merge(Vector<BinomialHeapNode *>& heap1, Vector<BinomialHeapNode* >& heap2);

    /*
     *  Method: mergeTrees
     *  Parameters: Vector<BinomialHeapNode *>& heap1
     *              Vector<BinomialHeapNode *>& heap2
     *  - - - - - - - - - - - - - - - - - -
     *  Takes two heaps of any size as reference parameters and
     *  returns the higher priority tree, with the lower priority
     *  tree now designated as one of the higher priority tree's
     *  children. This function is called only with trees of the
     *  same order, so it performs the trivial test of 
     *  comparing priorities using built-in operators of its node's
     *  entries.
     */
    void mergeTrees(BinomialHeapNode* & mergeTree, BinomialHeapNode* &tree1, BinomialHeapNode* &tree2);

    /*
     *  Method: inBounds
     *  Parameters: Vector<BinomialHeapNode *>& heap
     *              int index
     *  - - - - - - - - - - - - - - - - - -
     *  Helper function that determines whether a given
     *  index passed in is within bounds of a given
     *  vector passed by reference.
     */
    bool inBounds(Vector<BinomialHeapNode *>& heap, int index);

    /*
     *  Method: getDequeuedRoot
     *  Parameters: BinomialHeapNode*& dequeuedRoot
     *              int& dequeuedRootIndex
     *  - - - - - - - - - - - - - - - - - -
     *  Helper function that determines the root with the
     *  highest priority and returns the root via reference.
     *  The function also returns the index of the aforementioned
     *  root for use in the member variable that houses the 
     *  binomial heap. It determines the highest priority root
     *  by looping through each root of the binomial heap and 
     *  leveraging the built-in operators of the nodes' entries
     *  to determine equality.
     */
    void getDequeuedRoot(BinomialHeapNode*& dequeuedRoot, int& dequeuedRootIndex) const;
    
    /*
     *  Method: power
     *  Parameters: int base
     *              int exponent
     *  - - - - - - - - - - - - - - - - - -
     *  Helper function used to calculate the size
     *  of a binomial tree given its number of children.
     *  The function is generalized as a traditional
     *  power function that would return the correct value
     *  for positive parameters.
     */
    int power(int base, int exponent) const;

    /*
     *  Vector: heap
     *  - - - - - - - -
     *  The data type used to house the binomial heap,
     *  which itself is comprised of binomial trees.
     */
    Vector<BinomialHeapNode *> heap;
};

#endif
