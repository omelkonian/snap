#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "../graph_metrics/metrics.h"
#include "GraphLib.h"
#include "defines.h"

using namespace std;

#define PERSON_PROPERTIES_NUM 3
#define PERSON_REL_PROPERTIES_NUM 2

#define CHECK(text, actual, expected)                         \
  if (actual != expected) {                                   \
    printf("%-30s: Failed | actual = %3d, expected = %3d\n",  \
           text,                                              \
           actual,                                            \
           expected);                                         \
  } else {                                                    \
    printf("%-30s: Success\n", text);                     \
  }

/* Creates a node person and sets its properties */
Node* setPersonProperties(int id, char* name, char* surname, int age);
/* Creates an edge between two persons and sets its properties */
Edge* setEdgeProperties(int startNodeID, int endNodeID, char* type, int weight);
/* Prints a person's properties */
void printPersonProperties(Node* n);
/* Prints an edge's properties */
void printEdgeProperties(int startID, Edge* n);

int main_part1(void) {

	int m = 2;
	int c = 3;

	/*create empty graph*/
	Graph* g = createGraph(m, c);

	/*create node and set node properties*/
	Node* n1 = setPersonProperties(5, "lonely", "loner", 29);
	Node* n2 = setPersonProperties(1, "herald", "kllapi", 22);
	Node* n3 = setPersonProperties(2, "marialena", "kiriakidi", 25);
	Node* n4 = setPersonProperties(10, "antonia", "saravanou", 18);
	Node* n5 = setPersonProperties(6, "manos", "karvounis", 19);
	Node* n6 = setPersonProperties(3, "giannis", "chronis", 20);
	Node* n7 = setPersonProperties(4, "christoforos", "sfiggos", 16);
	Node* n8 = setPersonProperties(7, "stamatis", "xristoforidis", 24);
	Node* n9 = setPersonProperties(8, "xristos", "mallios", 29);
	Node* n10 = setPersonProperties(14, "johnny", "depp", 35);
	Node* n11 = setPersonProperties(12, "fox", "mulder", 29);
	Node* n12 = setPersonProperties(16, "dana", "scully", 25);

	/*insert nodes in graph*/
	insertNode(n1, g);
	insertNode(n2, g);
	insertNode(n3, g);
	insertNode(n4, g);
	insertNode(n5, g);
	insertNode(n6, g);
	insertNode(n7, g);
	insertNode(n8, g);
	insertNode(n10, g);
	insertNode(n9, g);
	insertNode(n11, g);
	insertNode(n12, g);

	/* Create edges and set properties */
	Edge* e1 = setEdgeProperties(1, 6, "knows", 30);
	Edge* e2 = setEdgeProperties(6, 1, "knows", 30);
	Edge* e3 = setEdgeProperties(1, 2, "knows", 20);
	Edge* e4 = setEdgeProperties(2, 1, "knows", 20);
	Edge* e5 = setEdgeProperties(1, 4, "knows", 30);
	Edge* e6 = setEdgeProperties(4, 1, "knows", 30);
	Edge* e7 = setEdgeProperties(2, 6, "knows", 10);
	Edge* e8 = setEdgeProperties(6, 2, "knows", 10);
	Edge* e9 = setEdgeProperties(4, 3, "knows", 30);
	Edge* e10 = setEdgeProperties(3, 4, "knows", 30);
	Edge* e11 = setEdgeProperties(4, 7, "knows", 30);
	Edge* e12 = setEdgeProperties(7, 4, "knows", 30);
	Edge* e13 = setEdgeProperties(4, 8, "knows", 10);
	Edge* e14 = setEdgeProperties(8, 4, "knows", 10);
	Edge* e15 = setEdgeProperties(3, 10, "knows", 30);
	Edge* e16 = setEdgeProperties(10, 3, "knows", 30);
	Edge* e17 = setEdgeProperties(10, 7, "knows", 30);
	Edge* e18 = setEdgeProperties(7, 10, "knows", 30);
	Edge* e19 = setEdgeProperties(10, 14, "knows", 50);
	Edge* e20 = setEdgeProperties(14, 10, "knows", 50);
	Edge* e21 = setEdgeProperties(14, 12, "knows", 30);
	Edge* e22 = setEdgeProperties(12, 14, "knows", 30);
	Edge* e23 = setEdgeProperties(12, 16, "knows", 30);
	Edge* e24 = setEdgeProperties(16, 12, "knows", 30);
	Edge* e25 = setEdgeProperties(16, 14, "knows", 30);
	Edge* e26 = setEdgeProperties(14, 16, "knows", 30);
//	Edge* e27 = setEdgeProperties(3, 8, "knows", 30);
//    Edge* e28 = setEdgeProperties(8, 3, "knows", 30);
//	Edge* e29 = setEdgeProperties(8, 10, "knows", 10);
//    Edge* e30 = setEdgeProperties(10, 8, "knows", 10);

	/* Insert edges in graph */
	insertEdge(1, e1, g);
	insertEdge(6, e2, g);
	insertEdge(1, e3, g);
	insertEdge(2, e4, g);
	insertEdge(1, e5, g);
	insertEdge(4, e6, g);
	insertEdge(2, e7, g);
	insertEdge(6, e8, g);
	insertEdge(4, e9, g);
	insertEdge(3, e10, g);
	insertEdge(4, e11, g);
	insertEdge(7, e12, g);
	insertEdge(4, e13, g);
	insertEdge(8, e14, g);
	insertEdge(3, e15, g);
	insertEdge(10, e16, g);
	insertEdge(10, e17, g);
	insertEdge(7, e18, g);
	insertEdge(10, e19, g);
	insertEdge(14, e20, g);
	insertEdge(14, e21, g);
	insertEdge(12, e22, g);
	insertEdge(12, e23, g);
	insertEdge(16, e24, g);
	insertEdge(16, e25, g);
	insertEdge(14, e26, g);

	/* Perform lookups in the graph */
	Node* nl1 = lookupNode(12, g);
	printPersonProperties(nl1);
	Node* nl2 = lookupNode(16, g);
	printPersonProperties(nl2);
	cout << endl;
	cout << endl;

	/* Find shortest path 1-1 */
	int spt1 = reachNode1(1, 12, g);
	CHECK("Shortest path between nodes (1,12)", spt1, 5);

	int spt2 = reachNode1(14, 14, g);
	CHECK("Shortest path between nodes (14,14)", spt2, 0);

	int spt3 = reachNode1(3, 16, g);
	CHECK("Shortest path between nodes (3,16)", spt3, 3);

	int spt4 = reachNode1(5, 3, g);
	CHECK("Shortest path between nodes (5,3)", spt4, INFINITY_REACH_NODE);

	/* Find shortest paths 1-N */
	ResultSet* res = reachNodeN(1, g);

	Pairr results[10] = { { 2, 1 }, { 6, 1 }, { 4, 1 }, { 3, 2 }, { 7, 2 }, { 8, 2 }, { 10, 3 }, { 14, 4 }, { 16, 5 }, { 12, 5 } };

	Pair* pair;
	int k;
	int counter = 0;
	while ((pair = res->next()) != NULL) {
		++counter;
		for (k = 0; k < 10; ++k) {
			if (results[k].ID == pair->getNodeId()) {
				if (results[k].distance == pair->getDistance()) {
					printf("Shortest path between nodes (%d,%d): Success\n", 1, results[k].ID);
				} else {
					printf("Shortest path between nodes (%d,%d): Failed | actual = %3d, expected = %3d\n", 1, results[k].ID, pair->getDistance(), results[k].distance);
				}
				break;
			}
		}
		if (k == 10) {
			printf("ReachNodeN : Failed | Your returned an extra Pair(%d,%d) ", pair->getNodeId(), pair->getDistance());
		}
	}
	CHECK("Number of pairs in the ResultSet", counter, 10);

	// Free ResultSet.
	delete res;
	delete g;

	return EXIT_SUCCESS;
}

Node* setPersonProperties(int id, char* name, char* surname, int age) {

	/*create properties*/
	Properties* prop = createProperties(PERSON_PROPERTIES_NUM);
	setStringProperty(name, 0, prop);
	setStringProperty(surname, 1, prop);
	setIntegerProperty(age, 2, prop);

	/*create node*/
	Node* n = createNode(id, prop);

	return n;
}

Edge* setEdgeProperties(int startNodeID, int endNodeID, char* type, int weight) {

	/*create edge properties*/
	Properties* propEdge = createProperties(PERSON_REL_PROPERTIES_NUM);
	setStringProperty(type, 0, propEdge);
	setIntegerProperty(weight, 1, propEdge);

	/*create an edge*/
	Edge* e = createEdge(startNodeID, endNodeID, propEdge);
	return e;
}

void printPersonProperties(Node* n) {
	n->print();
}

void printEdgeProperties(int startID, Edge* e) {
	e->print();
}

