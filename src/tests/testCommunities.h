/*
 * testCommunities.h
 *
 *  Created on: 8 ��� 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../communities/_communities.h"

void _testPreprocessing() {
	Graph **graphs = getTopNForums(20);
	for (int i = 0; i < 20; i++)
		graphs[i]->print();

	delete graphs;
}

void _testFindCommunities() {

	Graph *g = createGraph(2, 5);

	// create node and set node properties
	Node* n1 = _setPersonProperties2(5, "lonely", "loner", 29);
	Node* n2 = _setPersonProperties2(1, "herald", "kllapi", 22);
	Node* n3 = _setPersonProperties2(2, "marialena", "kiriakidi", 25);
	Node* n4 = _setPersonProperties2(10, "antonia", "saravanou", 18);
	Node* n5 = _setPersonProperties2(6, "manos", "karvounis", 19);
	Node* n6 = _setPersonProperties2(3, "giannis", "chronis", 20);
	Node* n7 = _setPersonProperties2(4, "christoforos", "sfiggos", 16);
	Node* n8 = _setPersonProperties2(7, "stamatis", "xristoforidis", 24);
	Node* n9 = _setPersonProperties2(8, "xristos", "mallios", 29);
	Node* n10 = _setPersonProperties2(14, "johnny", "depp", 35);
	Node* n11 = _setPersonProperties2(12, "fox", "mulder", 29);
	Node* n12 = _setPersonProperties2(16, "dana", "scully", 25);
	cout << "2) Created Nodes" << endl;

	//  insert nodes in graph

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
	cout << "3) Inserted Nodes" << endl;

	//    Create edges and set properties
	Edge* e1 = _setEdgeProperties2(1, 6, "knows", 30);
	Edge* e2 = _setEdgeProperties2(6, 1, "knows", 30);
	Edge* e3 = _setEdgeProperties2(1, 2, "knows", 20);
	Edge* e4 = _setEdgeProperties2(2, 1, "knows", 20);
	Edge* e5 = _setEdgeProperties2(1, 4, "knows", 30);
	Edge* e6 = _setEdgeProperties2(4, 1, "knows", 30);
	Edge* e7 = _setEdgeProperties2(2, 6, "knows", 10);
	Edge* e8 = _setEdgeProperties2(6, 2, "knows", 10);
	Edge* e9 = _setEdgeProperties2(4, 3, "knows", 30);
	Edge* e10 = _setEdgeProperties2(3, 4, "knows", 30);
	Edge* e11 = _setEdgeProperties2(4, 7, "knows", 30);
	Edge* e12 = _setEdgeProperties2(7, 4, "knows", 30);
	Edge* e13 = _setEdgeProperties2(4, 8, "knows", 10);
	Edge* e14 = _setEdgeProperties2(8, 4, "knows", 10);
	Edge* e15 = _setEdgeProperties2(3, 10, "knows", 30);
	Edge* e16 = _setEdgeProperties2(10, 3, "knows", 30);
	Edge* e17 = _setEdgeProperties2(10, 7, "knows", 30);
	Edge* e18 = _setEdgeProperties2(7, 10, "knows", 30);
	Edge* e19 = _setEdgeProperties2(10, 14, "knows", 50);
	Edge* e20 = _setEdgeProperties2(14, 10, "knows", 50);
	Edge* e21 = _setEdgeProperties2(14, 12, "knows", 30);
	Edge* e22 = _setEdgeProperties2(12, 14, "knows", 30);
	Edge* e23 = _setEdgeProperties2(12, 16, "knows", 30);
	Edge* e24 = _setEdgeProperties2(16, 12, "knows", 30);
	Edge* e25 = _setEdgeProperties2(16, 14, "knows", 30);
	Edge* e26 = _setEdgeProperties2(14, 16, "knows", 30);
	Edge* e27 = _setEdgeProperties2(3, 8, "knows", 30);
	Edge* e28 = _setEdgeProperties2(8, 3, "knows", 30);
	Edge* e29 = _setEdgeProperties2(8, 10, "knows", 10);
	Edge* e30 = _setEdgeProperties2(10, 8, "knows", 10);
	cout << "4) Created Edges" << endl;

	//     Insert edges in graph
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
	insertEdge(3, e27, g);
	insertEdge(8, e28, g);
	insertEdge(8, e29, g);
	insertEdge(10, e30, g);
	cout << "5) Inserted Edges" << endl;

	Graph* graph = loadGraph(7, 20);
	Communities* communities = g->findCommunities();
//		Communities* communities = findCommunities(graph);
	communities->getCommunitiesList()->print();

	delete communities;
}
