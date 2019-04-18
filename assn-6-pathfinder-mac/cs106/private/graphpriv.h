/*
 * File: graphpriv.h
 * Last modified on Sun Nov 29 08:39:35 2009 by eroberts
 * -----------------------------------------------------
 * This file defines the private data for the Graph class.
 */

/* Instance variables */

	Set<NodeType *> nodes;             /* The set of nodes in the graph */
	Set<ArcType *> arcs;               /* The set of arcs in the graph  */
	Map<NodeType *> nodeMap;           /* A map from names and nodes    */

/*
 * Functions: operator=, copy constructor
 * --------------------------------------
 * These functions are part of the public interface of the class but are
 * defined here to avoid adding confusion to the Graph class.
 */

public:
	const Graph & operator=(const Graph & rhs);
	Graph(const Graph & rhs);

private:
	void copyInternalData(const Graph & other);
