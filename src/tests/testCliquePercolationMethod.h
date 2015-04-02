/*
 * testCliquePercolationMethod.h
 *
 *  Created on: Jan 13, 2015
 *      Author: athan
 */

#ifndef TESTCLIQUEPERCOLATIONMETHOD_H_
#define TESTCLIQUEPERCOLATIONMETHOD_H_

#include "tests.h"
#include "../communities/Communities.h"
#include "../communities/_communities.h"

using namespace std;

void _testCliquePercolationMethod(){

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
//	g->insertNode(new Node(10, NULL));

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
	g->insertEdge(5, new Edge(5, 8, NULL));
	g->insertEdge(5, new Edge(5, 7, NULL));
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
//	g->insertEdge(10, new Edge(10, 7, NULL));
//	g->insertEdge(10, new Edge(10, 8, NULL));
//	g->insertEdge(10, new Edge(10, 6, NULL));
//	g->insertEdge(10, new Edge(10, 5, NULL));
//	g->insertEdge(8, new Edge(8, 10, NULL));
//	g->insertEdge(7, new Edge(7, 10, NULL));
//	g->insertEdge(6, new Edge(6, 10, NULL));
//	g->insertEdge(5, new Edge(5, 10, NULL));

	//Graph* graph = loadGraph(7,20);
	Communities* com = cliquePercolationMethod(3 , g);
	com->print();

	delete g;
	delete com;
}



#endif /* TESTCLIQUEPERCOLATIONMETHOD_H_ */
