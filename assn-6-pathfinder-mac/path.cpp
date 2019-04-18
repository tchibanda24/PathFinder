/*
 * File: path.cpp
 * --------------
 * Name: Thabani Chibanda
 * Section: Ashwin Siripurapu
 * This file implements the path.h interface.
 */

/*
 
 For implementation of path, I decided to have it so that the client can set
 the values for the start and finish node but they cannot get the nodes. These
 two values are going to be used by the class to find the path. The only thing
 that can be returned to the client is the distance of the path, and the string
 that shows the path. I decided that the method that finds the path will be
 private and called within the toString method that returns the entire path
 as a string. I chose to do it this way so that the client doesn't actually
 have access to all the methods where the real calculations are done. Rather
 they have to call other methods to retrieve the information for them.
 */

#include "path.h"
#include "genlib.h"
#include <typeinfo>

// [TODO: implement the methods in your Path class]

Path::Path(){
    start = new nodeT;
    finish = new nodeT;
    Vector<arcT> *finalPath = new Vector<arcT>;
    Graph<nodeT,arcT> *pathF = new Graph<nodeT,arcT>;
    distance = 0;
}

Path::~Path(){}

void Path::SetMap(Graph<nodeT,arcT> pathF2){
     *pathF = pathF2;
}

void Path::SetStart(nodeT strt){
    *start = strt;
}

void Path::SetFinish(nodeT fin){
    *finish = fin;
}

double Path::GetDistance(){
    if (finalPath) {
        Error("GetDistance: No current path at this point and time.");
    }
    
    foreach (arcT *arc in finalPath) {
        distance += arc->distance;
    }
}

string Path::toString(){
    
}

void Path::FindPath() {
    
    Vector<arcT *> path;
    Queue< Vector<arcT *> > queue;
    Map<double> fixed;
    
    while (start != finish) {
        if (!fixed.containsKey(start->name)) {
            fixed.put(start->name, TotalPathDistance(path));
            foreach (arcT *arc in start->arcs) {
                if (!fixed.containsKey(arc->finish->name)) {
                    Vector<arcT *> newPath = path;
                    newPath.add(arc);
                    
                    queue.enqueue(newPath, TotalPathDistance(newPath));
                }
            }
        }
        
        if (queue.isEmpty()) break;
        
        path = queue.dequeue();
        start = path[path.size() - 1]->finish;
    }
}

double Path::TotalPathDistance(Vector<arcT *> path) {
    double distance = 0;
    foreach (arcT *arc in path) {
        distance += arc->distance;
    }
    
    return distance;
}







