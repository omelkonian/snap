/*
 * testExtendedBFS.h
 *
 *  Created on: 30 Эях 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include <iostream>

#include "general.h"
#include "../search/ExtendedBFS.h"

using namespace std;

Node* _setPersonProperties(int id, char* name, char* surname, int age) {

	/*create properties*/
	Properties* prop = createProperties(PERSON_PROPERTIES_NUM);
	setStringProperty(name, 0, prop);
	setStringProperty(surname, 1, prop);
	setIntegerProperty(age, 2, prop);

	/*create node*/
	Node* n = createNode(id, prop);

	return n;
}

Edge* _setEdgeProperties(int startNodeID, int endNodeID, char* type, int weight) {

	/*create edge properties*/
	Properties* propEdge = createProperties(PERSON_REL_PROPERTIES_NUM);
	setStringProperty(type, 0, propEdge);
	setIntegerProperty(weight, 1, propEdge);

	/*create an edge*/
	Edge* e = createEdge(startNodeID, endNodeID, propEdge);
	return e;
}

void _testExtendedBFS() {
	Graph *g = createGraph(2, 5);

	/*create node and set node properties*/
	Node* n1 = _setPersonProperties(1, "lonely", "loner", 29);
	Node* n2 = _setPersonProperties(2, "herald", "kllapi", 22);
	Node* n3 = _setPersonProperties(3, "marialena", "kiriakidi", 25);
	Node* n4 = _setPersonProperties(4, "antonia", "saravanou", 18);
	Node* n5 = _setPersonProperties(5, "manos", "karvounis", 19);
	Node* n6 = _setPersonProperties(6, "giannis", "chronis", 20);
	Node* n7 = _setPersonProperties(7, "christoforos", "sfiggos", 16);
	Node* n8 = _setPersonProperties(8, "stamatis", "xristoforidis", 24);
	Node* n9 = _setPersonProperties(9, "xristos", "mallios", 29);
	Node* n10 = _setPersonProperties(11, "johnny", "depp", 35);

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

	/* Create edges and _set properties */
	Edge* e1 = _setEdgeProperties(1, 2, "knows", 30);
	Edge* e2 = _setEdgeProperties(1, 3, "knows", 30);
	Edge* e3 = _setEdgeProperties(2, 4, "knows", 20);
	Edge* e4 = _setEdgeProperties(2, 5, "knows", 20);
	Edge* e5 = _setEdgeProperties(3, 6, "knows", 30);
	Edge* e6 = _setEdgeProperties(3, 7, "knows", 30);
	Edge* e7 = _setEdgeProperties(4, 11, "knows", 10);
	Edge* e8 = _setEdgeProperties(5, 11, "knows", 10);
	Edge* e9 = _setEdgeProperties(6, 8, "knows", 30);
	Edge* e10 = _setEdgeProperties(6, 9, "knows", 30);
	Edge* e11 = _setEdgeProperties(6, 11, "knows", 30);
	Edge* e12 = _setEdgeProperties(7, 11, "knows", 30);
	Edge* e13 = _setEdgeProperties(7, 3, "knows", 10);

	insertEdge(1, e1, g);
	insertEdge(1, e2, g);
	insertEdge(2, e3, g);
	insertEdge(2, e4, g);
	insertEdge(3, e5, g);
	insertEdge(3, e6, g);
	insertEdge(4, e7, g);
	insertEdge(5, e8, g);
	insertEdge(6, e9, g);
	insertEdge(6, e10, g);
	insertEdge(6, e11, g);
	insertEdge(7, e12, g);
	insertEdge(7, e13, g);

	ExtendedBFS *ebfs = new ExtendedBFS(g, 1, 11, 6);
	ebfs->run();
	cout << "Total Shortest Paths: " << ebfs->getShortestPathNo() << endl;
	cout << "Paths Via Intermediate: " << ebfs->getShortestPathViaIntermediateNo() << endl;
}
