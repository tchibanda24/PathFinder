/*
 * File: pqueue.cpp
 * ----------------
 * This file provides a Vector-based implementation of the
 * pqueue.h interface.
 */

#ifdef _pqueue_h

#include "genlib.h"
#include "pqueue.h"
#include "vector.h"

/*
 * Implementation notes: PQueue constuctor and destructor
 * ------------------------------------------------------
 * All the work for the constructor and destructor is done by the
 * Vector class.
 */

template <typename ElemType>
PQueue<ElemType>::PQueue() {
    /* Empty */
}

template <typename ElemType>
PQueue<ElemType>::~PQueue() {
    /* Empty */
}

/*
 * Implementation notes: size, isEmpty, clear
 * ------------------------------------------
 * These implementations simply forward the request to the
 * underlying Vector object.
 */

template <typename ElemType>
int PQueue<ElemType>::size() {
    return entries.size();
}

template <typename ElemType>
bool PQueue<ElemType>::isEmpty() {
    return entries.isEmpty();
}

template <typename ElemType>
void PQueue<ElemType>::clear() {
    entries.clear();
}

/*
 * Implementation notes: enqueue
 * -----------------------------
 * This function finds where to insert a new element into the
 * queue and then calls insertAt to put it there.  Because
 * items are removed from the end of the queue, the highest
 * priority elements must be stored at the end of the queue.
 * Moreover, to ensure that elements obey the first-in/first-out
 * discipline when they have the same priority, the function must
 * insert each new element before any with the same priority.
 * Keep in mind that the base type of the vector is pqEntryT,
 * which contains both the element and the priority.
 */

template <typename ElemType>
void PQueue<ElemType>::enqueue(ElemType elem, double priority) {
    int index = 0;
	int size = entries.size();
    while (index < size && entries[index].priority > priority) {
        index++;
    }
    pqEntryT entry;
    entry.elem = elem;
    entry.priority = priority;
    entries.insertAt(index, entry);
}

/*
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These functions must check for an empty queue and report an
 * error if there are no entries.
 */

template <typename ElemType>
ElemType PQueue<ElemType>::dequeue() {
    if (isEmpty()) {
        Error("dequeue: Attempting to dequeue an empty queue");
    }
	int lastIndex = entries.size() - 1;
	ElemType result = entries[lastIndex].elem;
	entries.removeAt(lastIndex);
    return result;
}

template <typename ElemType>
ElemType PQueue<ElemType>::peek() {
    if (isEmpty()) {
        Error("peek: Attempting to peek at an empty queue");
    }
    return entries[entries.size() - 1].elem;
}

#endif
