#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GraphLib.h"
#include "defines.h"

/************************************/
/* Implement for test main purposes */
/************************************/

/**
 * Creates a properties object
 * number: the number of properties
 * return value: a properties object
 */
Properties* createProperties(int number) {
	Properties *ret = new Properties(number);
	return ret;
}

/**
 * Sets a string property "property" in position "index"
 * property: the type of the property
 * index: the position of the property
 * p: the properties object
 */
void setStringProperty(char* property, int index, Properties* p) {
	p->setStringProperty(property, index);
}

/**
 * Sets an integer property "property" in position "index"
 * property: the value of the property
 * index: the position of the property
 * p: the properties object
 */
void setIntegerProperty(int property, int index, Properties* p) {
	p->setIntegerProperty(property, index);
}

/**
 * Sets a double property "property" in position "index"
 * property: the type of the property
 * index: the position of the property
 * p: the properties object
 */
void setDoubleProperty(double property, int index, Properties* p) {
    p->setDoubleProperty(property, index);
}

/**
 * Gets a string property "property" from position "index"
 * index: the position of the requested property
 * p: the properties object
 * return value: the type of the property
 */
char* getStringProperty(int index, Properties* p) {
	return p->getStringProperty(index);
}

/**
 * Gets an integer property "property" from position "index"
 * index: the position of the requested property
 * p: the properties object
 * return value: the value of the property
 */
int getIntegerProperty(int index, Properties* p) {
	return p->getIntegerProperty(index);
}

/**
 * Gets a double property "property" from position "index"
 * index: the position of the requested property
 * p: the properties object
 * return value: the type of the property

 */
double getDoubleProperty(int index, Properties* p) {
    return p->getDoubleProperty(index);
}

/**
 * Creates a node with specific properties
 * id: the id of the node
 * p: the properties of the node
 * return value: the requested node
 */
Node* createNode(int id, Properties* p) {
	Node *ret = new Node(id, p);
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	return ret;
}

/**
 * Creates an edge with specific properties
 * startID: the id of the start node
 * endID: the id of the end node
 * p: the properties of the edge
 * return value: the requested edge
 */
Edge* createEdge(int startID, int endID, Properties* p) {
	Edge *ret = new Edge(startID, endID, p);
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	return ret;
}

/************************************/
/* Implement for part 1 */
/************************************/

/* Creates an empty graph
 * m: size of hashtable
 * c: size of cells in a bucket
 * return value: an empty graph*/
Graph* createGraph(int m, int c) {
	Graph *g = new Graph(m, c);
	if (!g) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	return g;
}

/* Destroys a graph
 * g: the graph
 * return value: success/fail status */
int destroyGraph(Graph* g) {
	delete g;
	return SUCCESS;
}

/* Inserts a node in the graph
 * n: the node to insert
 * g: the graph
 * return value: success/fail status */
int insertNode(Node* n, Graph* g) {
	g->insertNode(n);
	return SUCCESS;
}

/* Inserts an edge in the graph
 * startID: the id of the start node
 * e: the edge we want to add to the start node
 * g: the graph
 * return value: success/fail status */
int insertEdge(int startID, Edge* e, Graph* g) {
	g->insertEdge(startID, e);
	return SUCCESS;
}

/* Retrieves a node from the graph
 * nodeID: the if of node to retrieve
 * g: the graph
 * return value: the requested node */
Node* lookupNode(int nodeID, Graph* g) {
	return g->lookupNode(nodeID);
}

/* Finds shortest path distance between two nodes in an undirected graph with no edge weights
 * startID: the id of the start node
 * endID: the id of the end node
 * g: the graph
 * return value: the shortest path */
int reachNode1(int startID, int endID, Graph* g) {
	return g->reachNode1(startID, endID);
}

/* Finds shortest path distance between all reachable nodes from a given node
 * in an undirected graph with no edge weights
 * startID: the id of the start node
 * endID: the id of the end node
 * g: the graph
 * return value: a resultSet */
ResultSet* reachNodeN(int startID, Graph* g) {
	BFS *bfs = new BFS(g, startID);
	ResultSet * res = new ResultSet(bfs);
	if (!bfs || !res) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	return res;
}

