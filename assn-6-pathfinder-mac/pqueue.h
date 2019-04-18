/*
 * File: pqueue.h
 * --------------
 * This file provides the interface to the PQueue class, which
 * implements a simple priority queue.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "vector.h"

/*
 * Class: PQueue
 * -------------
 * This class that models a priority queue, which is similar to a
 * traditional queue except that the elements are inserted in
 * order of priority.  As in conventional English usage, lower
 * priority numbers correspond to higher priorities, so that a
 * priority 1 item must take precedence over a priority 2 item.
 */

template <typename ElemType>
class PQueue {
public:

/*
 * Constructor: PQueue
 * Usage: PQueue<int> pq;
 * ----------------------
 * The constructor initializes a new priority queue containing
 * elements of the specified type.
 */
    PQueue();

/*
 * Destructor: ~PQueue
 * Usage: (usually implicit)
 * -------------------------
 * The destructor deallocates storage associated with this queue.
 */
    ~PQueue();

/*
 * Method: size
 * Usage: nElems = pq.size();
 * --------------------------
 * Returns the number of elements in this priority queue.
 */
    int size();

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) . . .
 * ------------------------------
 * Returns true if this priority queue contains no elements,
 * and false otherwise.
 */
    bool isEmpty();

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from this priority queue.
 */
    void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(element, priority);
 * -------------------------------------
 * This method adds element to the priority queue with the
 * specified priority.  Lower priority numbers correspond to
 * higher priorities, which means that all priority 1 elements
 * are dequeued before any priority 2 elements.  If the priority
 * argument is omitted, elements are added at priority 0.
 */
    void enqueue(ElemType elem, double priority = 0);

/*
 * Method: dequeue
 * Usage: first = pq.dequeue();
 * ----------------------------
 * This method removes the highest-priority element from this queue
 * and returns it.
 */
    ElemType dequeue();

/*
 * Method: peek
 * Usage: first = pq.peek();
 * -------------------------
 * This method returns the value of highest-priority element in this
 * queue, without removing it.
 */
    ElemType peek();

private:

#include "pqueuepriv.h"

};

#include "pqueueimpl.cpp"

#endif
