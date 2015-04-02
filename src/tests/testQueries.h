/*
 * testQueries.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../queries/queries.h"
#include "../queries/Matches.h"
#include "../queries/Stalkers.h"
#include "../project_main/GraphQueries.h"

#include "../Node.h"
#include "../TrustNode.h"

using namespace std;

void _testQuery1() {
	Graph *g = loadGraph(1, 10);

	Node *n = g->lookupNode(557);
	cout << "ID: " << n->getId() << endl;
	cout << "Gender" << n->getProperties()->getStringProperty(2) << endl;
	cout << "Birthday: " << n->getProperties()->getStringProperty(3) << endl;

	Matches *matches = matchSuggestion(n, 0, 100, 35, 100, g);
	matches->print();

	assert(matches->getTopMatches()[0]->getID() == 680 && matches->getTopMatches()[1]->getID() == 655);
	assert(((int )(matches->getTopMatches()[0]->getSimilarityScore() * 100000)) == 5882);
	assert(((int )(matches->getTopMatches()[1]->getSimilarityScore() * 100000)) == 5555);

	delete matches;
	delete g;

	cout << "Freed all resources" << endl;

	return;
}

void _testQuery2() {
	int k = 10;
	int x = 150;
	int centralityMode = 1;
	Stalkers *st = new Stalkers(k);

	Graph *g = loadGraph(1, 100);

	Graph *stalkerGraph = getTopStalkers(k, x, centralityMode, g, st);
	stalkerGraph->print();

	/**
	 * METRICS COMPARISON BETWEEN THE TWO GRAPHS.
	 */
	cout << "=======================================================" << endl;
	cout << "                       Calculating metrics" << endl;
	cout << "=======================================================" << endl;

	// Density.
	cout << "Density of initial graph: " << density(g) << endl;
	cout << "Density of stalker graph: " << density(stalkerGraph) << endl;

	// Degree Distribution.
	degreeDistribution(g, false);
	degreeDistribution(stalkerGraph, false);

	// Diameter.
	cout << "Diameter of initial graph: " << diameter(g) << endl;
	cout << "Diameter of stalker graph: " << diameter(stalkerGraph) << endl;

	// Number of Connected Components.
	cout << "#connectedComponents of initial graph: " << numberOfCCs(g) << endl;
	cout << "#connectedComponents of stalker graph: " << numberOfCCs(stalkerGraph) << endl;

	// maxCC.
	cout << "maxCC of initial graph: " << maxCC(g) << endl;
	cout << "maxCC of stalker graph: " << maxCC(stalkerGraph) << endl;

	// Average path length.
	cout << "Average path length of initial graph: " << averagePathLength(g) << endl;
	cout << "Average path length of stalker graph: " << averagePathLength(stalkerGraph) << endl;

	delete g;
	cout << "______" << endl;
	delete stalkerGraph;
	cout << "______" << endl;
	delete st;
}
void _testQuery3() {

	int k = 10;
	char **menTrends; //= new char*[k];
	char **womenTrends; // = new char*[k];
	/*for(int i; i< k ; i++){
	 menTrends[i] = new char[MAX_WORD];
	 womenTrends[i] = new char[MAX_WORD];
	 }*/

	/*
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
	 Edge* e10 =_setEdgeProperties2(3, 4, "knows", 30);
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

	 */

	Graph* g = loadGraph(7, 20);
	cout << "Person Knows Person loaded" << endl;
	findTrends(k, g, &womenTrends, &menTrends);

	for (int i = 0; i < k; i++)
		cout << i << "." << menTrends[i] << endl;

	cout << "--------------------------------------" << endl;

	for (int i = 0; i < k; i++)
		cout << i << "." << womenTrends[i] << endl;

	for (int i = 0; i < k; i++) {
		delete[] menTrends[i];
		delete[] womenTrends[i];
	}
	delete[] menTrends;
	delete[] womenTrends;

	delete g;
}

void _testQuery4() {

	char *forum = "Wall of Wilson Alves";
//	char *forum = "Group for Euripides in Peru";
//	char *forum = "Album 7 of Meera Kapoor";

	Graph *g = loadGraph(7, 50);

	Graph* trustG = buildTrustGraph(forum, g);

	Node* startNode = trustG->lookupNode(334);
	Node* endNode = trustG->lookupNode(507);
	assert(startNode!=NULL);
	assert(endNode!=NULL);
	cout << "Estimate Trust: " << (double) estimateTrust(startNode, endNode, trustG) << endl;
//	trustG->print();

	delete g;
	delete trustG;

//	Graph* graph = new Graph(5,5);
//
//	Properties* properties0 = new Properties(2);
//	properties0->setDoubleProperty(-1.0,0);
//	properties0->setIntegerProperty(INT_MAX,1);
//	TrustNode* n0 = new TrustNode(0,NULL,properties0);
//
//	Properties* properties1 = new Properties(2);
//	properties1->setDoubleProperty(-1.0,0);
//	properties1->setIntegerProperty(INT_MAX,1);
//	TrustNode* n1 = new TrustNode(1,NULL,properties1);
//
//	Properties* properties2 = new Properties(2);
//	properties2->setDoubleProperty(-1.0,0);
//	properties2->setIntegerProperty(INT_MAX,1);
//	TrustNode* n2 = new TrustNode(2,NULL,properties2);
//
//	Properties* properties3 = new Properties(2);
//	properties3->setDoubleProperty(-1.0,0);
//	properties3->setIntegerProperty(INT_MAX,1);
//	TrustNode* n3 = new TrustNode(3,NULL,properties3);
//
//	Properties* properties4 = new Properties(2);
//	properties4->setDoubleProperty(-1.0,0);
//	properties4->setIntegerProperty(INT_MAX,1);
//	TrustNode* n4 = new TrustNode(4,NULL,properties4);
//
//	Properties* properties5 = new Properties(2);
//	properties5->setDoubleProperty(-1.0,0);
//	properties5->setIntegerProperty(INT_MAX,1);
//	TrustNode* n5 = new TrustNode(5,NULL,properties5);
//
//	Properties* properties6 = new Properties(2);
//	properties6->setDoubleProperty(-1.0,0);
//	properties6->setIntegerProperty(INT_MAX,1);
//	TrustNode* n6 = new TrustNode(6,NULL,properties6);
//
//	Properties* properties7 = new Properties(2);
//	properties7->setDoubleProperty(-1.0,0);
//	properties7->setIntegerProperty(INT_MAX,1);
//	TrustNode* n7 = new TrustNode(7,NULL,properties7);
//
//	Properties* properties8 = new Properties(2);
//	properties8->setDoubleProperty(-1.0,0);
//	properties8->setIntegerProperty(INT_MAX,1);
//	TrustNode* n8 = new TrustNode(8,NULL,properties8);
//
//	insertNode(n0, graph);
//	insertNode(n1, graph);
//	insertNode(n2, graph);
//	insertNode(n3, graph);
//	insertNode(n4, graph);
//	insertNode(n5, graph);
//	insertNode(n6, graph);
//	insertNode(n7, graph);
//	insertNode(n8, graph);
//
//	 Properties* trustEdgeProperties0 = new Properties(2);
//	 trustEdgeProperties0->setStringProperty("trusts",0);
//	 trustEdgeProperties0->setDoubleProperty(0.9,1);
//	 Edge* trustEdge0 = new Edge(0,1,trustEdgeProperties0);
//	 graph->insertEdge(0,trustEdge0);
//
//	 Properties* trustEdgeProperties1 = new Properties(2);
//	 trustEdgeProperties1->setStringProperty("trusts",0);
//	 trustEdgeProperties1->setDoubleProperty(1.0,1);
//	 Edge* trustEdge1 = new Edge(0,2,trustEdgeProperties1);
//	 graph->insertEdge(0,trustEdge1);
//
//	 Properties* trustEdgeProperties2 = new Properties(2);
//	 trustEdgeProperties2->setStringProperty("trusts",0);
//	 trustEdgeProperties2->setDoubleProperty(1.0,1);
//	 Edge* trustEdge2 = new Edge(0,3,trustEdgeProperties2);
//	 graph->insertEdge(0,trustEdge2);
//
//	 Properties* trustEdgeProperties3 = new Properties(2);
//	 trustEdgeProperties3->setStringProperty("trusts",0);
//	 trustEdgeProperties3->setDoubleProperty(0.8,1);
//	 Edge* trustEdge3 = new Edge(1,5,trustEdgeProperties3);
//	 graph->insertEdge(1,trustEdge3);
//
//	 Properties* trustEdgeProperties4 = new Properties(2);
//	 trustEdgeProperties4->setStringProperty("trusts",0);
//	 trustEdgeProperties4->setDoubleProperty(0.6,1);
//	 Edge* trustEdge4 = new Edge(2,5,trustEdgeProperties4);
//	 graph->insertEdge(2,trustEdge4);
//
//	 Properties* trustEdgeProperties5 = new Properties(2);
//	 trustEdgeProperties5->setStringProperty("trusts",0);
//	 trustEdgeProperties5->setDoubleProperty(1.0,1);
//	 Edge* trustEdge5 = new Edge(3,4,trustEdgeProperties5);
//	 graph->insertEdge(3,trustEdge5);
//
//	 Properties* trustEdgeProperties6 = new Properties(2);
//	 trustEdgeProperties6->setStringProperty("trusts",0);
//	 trustEdgeProperties6->setDoubleProperty(0.9,1);
//	 Edge* trustEdge6 = new Edge(4,5,trustEdgeProperties6);
//	 graph->insertEdge(4,trustEdge6);
//
//	 Properties* trustEdgeProperties7 = new Properties(2);
//	 trustEdgeProperties7->setStringProperty("trusts",0);
//	 trustEdgeProperties7->setDoubleProperty(0.9,1);
//	 Edge* trustEdge7 = new Edge(5,6,trustEdgeProperties7);
//	 graph->insertEdge(5,trustEdge7);
//
//	 Properties* trustEdgeProperties8 = new Properties(2);
//	 trustEdgeProperties8->setStringProperty("trusts",0);
//	 trustEdgeProperties8->setDoubleProperty(1.0,1);
//	 Edge* trustEdge8 = new Edge(6,7,trustEdgeProperties8);
//	 graph->insertEdge(6,trustEdge8);
//
//	 Node* startNode = graph->lookupNode(0);
//	 Node* endNode = graph->lookupNode(7);
//
//	cout<<"Estimate Trust: "<<(double) estimateTrust(startNode,endNode, graph)<<endl;
//	delete graph;
}
