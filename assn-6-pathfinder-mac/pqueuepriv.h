/*
 * File: pqueuepriv.h
 * ------------------
 * This file describes the private section of the PQueue class.
 * This implementation uses a Vector as its underlying representation,
 * both to simplify the implementation and to ensure that the class
 * behaves correctly when copied.
 */

/* Type used for each priority queue entry */

	struct pqEntryT {
		ElemType elem;
		double priority;
	};

/* Instance variables */

	Vector<pqEntryT> entries;     /* The vector of pqEntryT values */
