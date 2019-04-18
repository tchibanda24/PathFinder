/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: Thabani Chibanda
 * Section: Ashwin Siripurapu
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 
// [TODO: complete this implementation]

#include "genlib.h"
#include "gpathfinder.h"
#include "simpio.h"
#include "scanner.h"
#include "graphtypes.h"
#include "graph.h"
#include "vector.h"
#include "Queue.h"
#include "path.h"
#include <iostream>
#include <fstream>

/* Function prototypes */

void QuitAction();
void NewMap(Graph<nodeT,arcT> &pathF);
void NewNode(Graph<nodeT,arcT> &pathF, Scanner &scanner, string &currToken);
void NewArcs(Graph<nodeT,arcT> &pathF, Scanner &scanner, string &currToken, string map);
void CheckIncoming(string &currToken, bool &nodes, bool &arcs, Scanner &scanner);
void CheckFile(string &text, ifstream &infile);
void DrawMap(string &map);
Vector<arcT *> FindShortest(Graph<nodeT,arcT> &pathF);
double TotalPathDistance(Vector<arcT *> path);

/* Main program */

int main() {
    
    Graph<nodeT,arcT> *pathF = new Graph<nodeT, arcT>;
    
	InitPathfinderGraphics();
    AddButton("Map", NewMap, *pathF);
    AddButton("Dijkstra", FindShortest, *pathF);
    AddButton("Kruscal", NewMap, *pathF);
	AddButton("Quit", QuitAction);
    
	PathfinderEventLoop();
    return 0;
}

/* Sample callback function */

void QuitAction() {
	exit(0);
}

/**
 * Function that creates a new graph and displays the new map
 * in the graphics window
 *
 * @param the pathfinder graph
 * @return void
 */
void NewMap(Graph<nodeT,arcT> &pathF) {
    
    Scanner scanner;
    scanner.setSpaceOption(Scanner::IgnoreSpaces);
    
    ifstream infile;
    string text, map;
    bool nodes = false, arcs = false;
    
    cout << "Please enter the name of the graph data file: ";
    text = GetLine();
    infile.open(text.c_str());
    CheckFile(text, infile);
    
    scanner.setInput(infile);
    
    while (scanner.hasMoreTokens()) {
        string currToken;
        
        currToken = scanner.nextToken();
        
        CheckIncoming(currToken, nodes, arcs, scanner);
        
        if ((nodes == false) && (arcs == false)) {
            string place, dot, ext;
            place = currToken;
            dot = scanner.nextToken();
            ext = scanner.nextToken();
            
            map = place + dot + ext;
            DrawMap(map);
        }
        
        if (nodes == true) {
            NewNode(pathF, scanner, currToken);
        }
        
        if (arcs == true) {
            NewArcs(pathF, scanner, currToken, map);
        }
    }
    
}

/**
 * Helper function that creates a new node on the graph and then displays it
 * on the map
 *
 * @param the pathfinder graph, scanner, and the current token in the text file
 * @return void
 */
void NewNode(Graph<nodeT,arcT> &pathF, Scanner &scanner, string &currToken){
    
    string name;
    int x, y;
    pointT *currPoint = new pointT;
    nodeT *currNode = new nodeT;
    
    name = currToken;
    x = StringToInteger(scanner.nextToken());
    y = StringToInteger(scanner.nextToken());
    
    currPoint->x = x;
    currPoint->y = y;
    
    currNode->name = name;
    currNode->loc = *currPoint;
    
    pathF.addNode(currNode);
    DrawPathfinderNode(*currPoint, "black", name);
    UpdatePathfinderDisplay();
    
}

/**
 * Helper function that creates a new arc in the graph and then displays it
 * on the map in the appropriate place
 *
 * @param the pathfinder graph, scanner, and the current token in the text file,
 *        and the map to be used(this is because taking in the distances for the
 *        Stanford map had to be handled a bit differently)
 * @return void
 */
void NewArcs(Graph<nodeT,arcT> &pathF, Scanner &scanner, string &currToken, string map) {
    
    string start, finish;
    double distance;
    arcT *currArc = new arcT;
    
    start = currToken;
    finish = scanner.nextToken();
    
    if (map == "Stanford.jpg") {
        string first, dot, next;
        first = scanner.nextToken();
        dot = scanner.nextToken();
        next = scanner.nextToken();
        
        distance = StringToReal(first + dot + next);
    }
    else {
        distance = StringToReal(scanner.nextToken());
    }
    
    currArc->start = pathF.getNode(start);
    currArc->finish = pathF.getNode(finish);
    currArc->distance = distance;
    
    pathF.addArc(currArc);
    
    currArc = new arcT;
    
    currArc->start = pathF.getNode(finish);
    currArc->finish = pathF.getNode(start);
    currArc->distance = distance;
    
    pathF.addArc(currArc);
    
    currArc->start->arcs.add(currArc);
    currArc->finish->arcs.add(currArc);
    
    DrawPathfinderArc(currArc->start->loc, currArc->finish->loc, "black");
    UpdatePathfinderDisplay();
}

/**
 * Helper function that puts up the original empty map
 *
 * @param the name of the map
 * @return void
 */
void DrawMap(string &map){
    
    DrawPathfinderMap(map);
    
    UpdatePathfinderDisplay();
    
}

/**
 * This helper function checks to see whether the scanner is currently looking
 * at the nodes or the arcs within the text file
 *
 * @param and the current token in the text file, boolean values specifying what
 *        is being looked at, and a scanner object
 * @return void
 */
void CheckIncoming(string &currToken, bool &nodes, bool &arcs, Scanner &scanner) {
    
    if (currToken == "NODES") {
        nodes = true;
        arcs = false;
        
        currToken = scanner.nextToken();
    }
    else if (currToken == "ARCS") {
        nodes = false;
        arcs = true;
        
        currToken = scanner.nextToken();
    }
}

/**
 * Helper function that checks to see if the file given is real or not
 *
 * @param the text file being entered and the ifstream with it
 * @return void
 */
void CheckFile(string &text, ifstream &infile){
	
	while (infile.fail()) {
		cout << text + " does not exist. Try again.\n";
		
		cout << "Please Enter File Name: ";
		text = GetLine();
		infile.open(text.c_str());
		
	}
}

/**
 * This should be the method where the path class is used to help find the shortest
 * path yet I wasn't able to get a working implementation of the class finished
 * before the hard deadline
 *
 * @param the graph with all the nodes and arcs
 * @return void
 */
Vector<arcT *> FindShortest(Graph<nodeT,arcT> &pathF){
    
    nodeT start, finish;
    double distance = 0;
    
    Path pathFinder;
    
    pathFinder.SetStart(start);
    pathFinder.SetFinish(finish);
    
    pathFinder.toString();
    
    distance  = pathFinder.GetDistance();
}


    


















