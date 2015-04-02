/*
 * testMetrics.h
 *
 *  Created on: 29 ��� 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../graph_metrics/metrics.h"
#include <iostream>
#include <math.h>
#include <assert.h>


using namespace std;

void printScores(long double **scores, int nodes, LinearHashTable *idMap);

void _testDiameter() {
	Graph *g = loadGraph(7, 10);
	int ret = diameter(g);
	cout << "Diameter: " << ret << endl;
	assert(ret == 6);
	delete g;
}

void _testDensity() {
	Graph *g = createGraph1(2, 5);
	cout << "Created Graph, edgeNo:" << g->getEdgeNo() << " nodeNo:" << g->getNodeNo() << endl;
	double ret = density(g);
	cout.precision(15);
	cout << "Density: " << fixed << ret << endl;
	assert(int(ret * 1000) == 20);

	delete g;
}

void _testDegreeDistribution() {
	Graph *g = createGraph1(2, 5);
	degreeDistribution(g, true);

	Graph *g2 = loadGraph(1, 100);
	degreeDistribution(g2, false);
}

void _testClosenessCentrality() {
	Graph *g = loadGraph(2, 5);
	Node *n = g->lookupNode(1);
	double ret = closenessCentrality(n, g);
	cout << "ClosenessCentrality: " << ret << endl;
	assert(int(ret*1000) == 317);
	delete g;
}

Node* _setPersonProperties2(int id, char* name, char* surname, int age) {

	/*create properties*/
	Properties* prop = createProperties(PERSON_PROPERTIES_NUM);
	setStringProperty(name, 0, prop);
	setStringProperty(surname, 1, prop);
	setIntegerProperty(age, 2, prop);

	/*create node*/
	Node* n = createNode(id, prop);

	return n;
}

Edge* _setEdgeProperties2(int startNodeID, int endNodeID, char* type, int weight) {

	/*create edge properties*/
	Properties* propEdge = createProperties(PERSON_REL_PROPERTIES_NUM);
	setStringProperty(type, 0, propEdge);
	setIntegerProperty(weight, 1, propEdge);

	/*create an edge*/
	Edge* e = createEdge(startNodeID, endNodeID, propEdge);
	return e;
}

void _testBetweennessCentrality() {
//	Graph *g = createGraph(2, 5);
//
//	Node* n1 = _setPersonProperties2(1, "lonely", "loner", 29);
//	Node* n2 = _setPersonProperties2(2, "herald", "kllapi", 22);
//	Node* n3 = _setPersonProperties2(3, "marialena", "kiriakidi", 25);
//	Node* n4 = _setPersonProperties2(4, "antonia", "saravanou", 18);
//	Node* n5 = _setPersonProperties2(5, "manos", "karvounis", 19);
//	Node* n6 = _setPersonProperties2(6, "giannis", "chronis", 20);
//
//	insertNode(n1, g);
//	insertNode(n2, g);
//	insertNode(n3, g);
//	insertNode(n4, g);
//	insertNode(n5, g);
//	insertNode(n6, g);
//
//	Edge* e1 = _setEdgeProperties2(1, 2, "knows", 30);
//	Edge* e2 = _setEdgeProperties2(1, 3, "knows", 30);
//	Edge* e3 = _setEdgeProperties2(2, 4, "knows", 30);
//	Edge* e4 = _setEdgeProperties2(2, 5, "knows", 30);
//	Edge* e5 = _setEdgeProperties2(2, 6, "knows", 30);
//	Edge* e6 = _setEdgeProperties2(3, 4, "knows", 30);
//	Edge* e7 = _setEdgeProperties2(3, 5, "knows", 10);
//	Edge* e8 = _setEdgeProperties2(3, 6, "knows", 10);
//
//	insertEdge(1, e1, g);
//	insertEdge(1, e2, g);
//	insertEdge(2, e3, g);
//	insertEdge(2, e4, g);
//	insertEdge(2, e5, g);
//	insertEdge(3, e6, g);
//	insertEdge(3, e7, g);
//	insertEdge(3, e8, g);
//
//	double ret = betweennessCentrality(n3, g);
//	assert(ret == 0.15);

	Graph *g = loadGraph(10, 100);
	double ret = betweennessCentrality(g->lookupNode(1734), g);

	cout << "BetweennessCentrality: " << ret << endl;

	delete g;
}

void _testAveragePathLength() {
	cout << "-----Testing AveragePathLength-----" << endl;

	Graph* g = loadGraph(7, 20);

	double ret = averagePathLength(g);
	cout << "AveragePathLength: " << ret << endl;

	assert(floor(ret*100) == 267);
}

void _testNumberOfCCs() {

	cout << "-----Testing numberOfCCs-----" << endl;

	Graph* g = loadGraph(7, 20);

	cout << "Number of Connected Graphs: " << numberOfCCs(g) << endl;
	//cout <<"Max number of Nodes in a Connected Graph: "<<maxCC(g)<<endl;
}

void _testMaxCC() {

	cout << "-----Testing maxCC-----" << endl;

	Graph* g = loadGraph(7, 20);

	cout << "Max number of Nodes in a Connected Graph: " << maxCC(g) << endl;

}

void _testEdgeBetweeness() {
	// Example from the .pdf given.
	Graph *g = new Graph(1, 5);
	g->insertNode(new Node(1, NULL));
	g->insertNode(new Node(2, NULL));
	g->insertNode(new Node(3, NULL));
	g->insertNode(new Node(4, NULL));
	g->insertNode(new Node(5, NULL));
	g->insertNode(new Node(6, NULL));
	g->insertNode(new Node(7, NULL));
	g->insertNode(new Node(8, NULL));
	g->insertNode(new Node(9, NULL));

	g->insertEdge(1, new Edge(1, 2, NULL));
	g->insertEdge(1, new Edge(1, 3, NULL));
	g->insertEdge(1, new Edge(1, 4, NULL));
	g->insertEdge(2, new Edge(2, 1, NULL));
	g->insertEdge(2, new Edge(2, 3, NULL));
	g->insertEdge(3, new Edge(3, 1, NULL));
	g->insertEdge(3, new Edge(3, 2, NULL));
	g->insertEdge(3, new Edge(3, 4, NULL));
	g->insertEdge(4, new Edge(4, 1, NULL));
	g->insertEdge(4, new Edge(4, 3, NULL));
	g->insertEdge(4, new Edge(4, 5, NULL));
	g->insertEdge(4, new Edge(4, 6, NULL));
	g->insertEdge(5, new Edge(5, 4, NULL));
	g->insertEdge(5, new Edge(5, 6, NULL));
	g->insertEdge(5, new Edge(5, 7, NULL));
	g->insertEdge(5, new Edge(5, 8, NULL));
	g->insertEdge(6, new Edge(6, 4, NULL));
	g->insertEdge(6, new Edge(6, 5, NULL));
	g->insertEdge(6, new Edge(6, 7, NULL));
	g->insertEdge(6, new Edge(6, 8, NULL));
	g->insertEdge(7, new Edge(7, 5, NULL));
	g->insertEdge(7, new Edge(7, 6, NULL));
	g->insertEdge(7, new Edge(7, 8, NULL));
	g->insertEdge(7, new Edge(7, 9, NULL));
	g->insertEdge(8, new Edge(8, 5, NULL));
	g->insertEdge(8, new Edge(8, 6, NULL));
	g->insertEdge(8, new Edge(8, 7, NULL));
	g->insertEdge(9, new Edge(9, 7, NULL));

	int nodes = g->getNodeNo();
	LinearHashTable *idMap = new LinearHashTable(1, 10);
	LinearHashTable *idMapReverse = new LinearHashTable(1, 10);
	List *allIDs = g->getAllIDs();
	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	for (int i = 0; i < nodes; i++) {
		Properties *prop = new Properties(1);
		prop->setIntegerProperty(i, 0);
		idMap->Insert(new Node(ili->getInt(), prop));

		Properties *prop2 = new Properties(1);
		prop2->setIntegerProperty(ili->getInt(), 0);
		idMapReverse->Insert(new Node(i, prop2));
		ili = ili->getNext();
	}

	long double **scores = computeEdgeBetweeness(g, idMap);
	printScores(scores, nodes, idMapReverse);

	int appear1 = 0, appear2 = 0, appear3 = 0, appear4 = 0, appear6 = 0, appear8 = 0, appear9 = 0, appear10 = 0;
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			switch ((int) scores[i][j]) {
			case 1:
				appear1++;
				break;
			case 2:
				appear2++;
				break;
			case 3:
				appear3++;
				break;
			case 4:
				appear4++;
				break;
			case 6:
				appear6++;
				break;
			case 8:
				appear8++;
				break;
			case 9:
				appear9++;
				break;
			case 10:
				appear10++;
				break;
			}
		}
	}
	assert(appear1 == 4);
	assert(appear2 == 2);
	assert(appear3 == 4);
	assert(appear4 == 4);
	assert(appear6 == 4);
	assert(appear8 == 2);
	assert(appear9 == 4);
	assert(appear10 == 4);

}

void printScores(long double **scores, int nodes, LinearHashTable *idMap) {
	cout << "Printing Edge Betweeness scores" << endl;
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			int realID1 = idMap->Lookup(i)->getNode()->getProperties()->getIntegerProperty(0);
			int realID2 = idMap->Lookup(j)->getNode()->getProperties()->getIntegerProperty(0);
			cout << realID1 << ":" << realID2 << " -> " << scores[i][j] << endl;
		}
	}
}
